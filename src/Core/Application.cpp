#include <iostream>

#include <glad/glad.h>
#include <vector>

#include "Application.h"
#include "EngineConfig.h"
#include "Clock.h"
#include "Services.h"
#include "../Platform/IWindow.h"
#include "../Platform/GLFWWindow.h"
#include "../Platform/Input.h"
#include "../Graphics/CubeRenderer.h"
#include "../Graphics/Camera.hpp"
#include "../Graphics/ChunkMesh.h"
#include "../GL/ShaderProgram.h"

#include "../World/Chunk.h"
#include "../World/Universe.h"

using namespace GameCore;
using namespace GamePlatform;
using namespace GameGraphics;

namespace GameCore
{
    Application::Application() = default;
    Application::~Application()
    {
        shutdown();

        delete _clock;
        delete _config;
    }

    bool Application::init(int argc, char **argv)
    {
        _clock = new Clock();
        _config = new EngineConfig();

        return true;
    }

    void Application::shutdown()
    {
        glfwTerminate();
    }

    void Application::update(std::shared_ptr<Services> services)
    {
        std::shared_ptr<Camera> camera = services->get<Camera>();
        std::shared_ptr<Input> input = services->get<Input>();
        std::shared_ptr<Universe> universe = services->get<Universe>();
        // Timers, Events, Input polling
        universe->update(camera->Position);

        // Camera movement
        if (Input::isKeyDown(Key::W))
            camera->ProcessKeyboard(Camera_Movement::FORWARD, _clock->deltaSeconds());
        else if (Input::isKeyDown(Key::S))
            camera->ProcessKeyboard(Camera_Movement::BACKWARD, _clock->deltaSeconds());
        if (Input::isKeyDown(Key::A))
            camera->ProcessKeyboard(Camera_Movement::LEFT, _clock->deltaSeconds());
        else if (Input::isKeyDown(Key::D))
            camera->ProcessKeyboard(Camera_Movement::RIGHT, _clock->deltaSeconds());
    }

    int Application::run(int argc, char **argv)
    {
        std::shared_ptr<Services> services = std::make_shared<Services>();

        if (!init(argc, argv))
            return -1;

        std::shared_ptr<GLFWWindow> window = std::make_shared<GLFWWindow>();
        WindowDesc wd;
        wd.width = config().get().windowWidth;
        wd.height = config().get().windowHeight;
        wd.title = config().get().windowTitle.c_str();
        wd.vsync = config().get().vsync;

        if (!window->create(wd))
            return 1;

        window->setCloseCallback([&]()
                                 { requestQuit(); });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            return 1;
        }
        services->set<IWindow>(window);

        std::shared_ptr<Camera> camera = std::make_shared<Camera>();
        services->set<Camera>(camera);

        std::shared_ptr<Input> input = std::make_shared<Input>(window->nativeHandle());
        services->set<Input>(input);

        bool firstMouse = true;
        float lastX;
        float lastY;
        input->mouseMove([&firstMouse, &lastX, &lastY, &camera](double xPos, double yPos)
                         {
            float f_xPos = static_cast<float>(xPos);
            float f_yPos = static_cast<float>(yPos);

            if (firstMouse)
            {
                lastX = f_xPos;
                lastY = f_yPos;
                firstMouse = false;
            }

            float xOffset = f_xPos - lastX;
            float yOffset = lastY - f_yPos;

            lastY = f_yPos;
            lastX = f_xPos;

            camera->ProcessMouseMovement(xOffset, yOffset); });

        // Test cube renderer
        std::shared_ptr<CubeRenderer> _testRenderer = std::make_shared<CubeRenderer>();
        services->set<CubeRenderer>(_testRenderer);

        // Universe / Game World
        std::shared_ptr<Universe> universe = std::make_shared<Universe>(glm::vec3(0));
        universe->update(glm::vec3(0));
        services->set<Universe>(universe);

        ShaderProgram shader("assets/shaders/BasicVert.glsl", "assets/shaders/BasicFrag.glsl");

        glm::vec3 lightPos(-10.f, 30.f, -10.f);
        glm::vec3 lightColor(1.f, 1.f, 1.f);
        shader.setVec3("u_LightPos", lightPos);
        shader.setVec3("u_LightColor", lightColor);

        while (_running && !window->shouldClose())
        {
            _clock->tick();
            window->pollEvents();

            update(services);

            // Renderer calls.
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            // Clear both color and depth each frame to avoid stale depth values
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();
            shader.setMat4("u_View", camera->GetViewMatrix());
            shader.setMat4("u_Projection", camera->GetPerspectiveMatrix());
            shader.setVec3("u_ViewPos", camera->Position);

            for (auto &[pos, chunk] : universe->getRenderList())
            {
                shader.setMat4("u_Model", glm::translate(glm::mat4(1.0f), glm::vec3(pos.x * 16, 1, pos.y * 16)));

                std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData = universe->getRenderList();

                chunk->getMesh(renderData)->getVAO().Bind();
                (glDrawElements(GL_TRIANGLES, floor(chunk->getMesh(renderData)->getVerticeCount() / 4) * 6, GL_UNSIGNED_INT, 0));
                chunk->getMesh(renderData)->getVAO().Unbind();
            }

            window->swapBuffers();
        }

        shutdown();
        return 0;
    }
}