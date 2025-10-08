#include <iostream>

#include <glad/glad.h>

#include "Application.h"
#include "EngineConfig.h"
#include "Clock.h"
#include "Services.h"
#include "../Platform/IWindow.h"
#include "../Platform/GLFWWindow.h"
#include "../Platform/Input.h"
#include "../Graphics/CubeRenderer.h"
#include "../Graphics/Camera.hpp"

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
    }

    void Application::update(std::shared_ptr<Services> services)
    {
        std::shared_ptr<Camera> camera = services->get<Camera>();
        std::shared_ptr<Input> input = services->get<Input>();
        // Timers, Events, Input polling

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

            camera->ProcessMouseMovement(xOffset, yOffset);
        });


        std::shared_ptr<CubeRenderer> _testRenderer = std::make_shared<CubeRenderer>();
        services->set<CubeRenderer>(_testRenderer);

        while (_running && !window->shouldClose())
        {
            _clock->tick();
            window->pollEvents();

            update(services);
            
            // Renderer calls.
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            // Clear both color and depth each frame to avoid stale depth values
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render test cube at origin so it's inside clip space for the simple shader
           for (float x = 0; x < 100; x += 1.1)
           {
            for (float y = 0; y < 100; y += 1.1)
            {
                _testRenderer->renderCube(camera, glm::vec3(x, ((x / 10) + (y / 10)), y));
            }
           }

            window->swapBuffers();
        }

        shutdown();
        return 0;
    }
}