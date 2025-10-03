#include <iostream>

#include <glad/glad.h>

#include "Application.h"
#include "EngineConfig.h"
#include "Clock.h"
#include "../Platform/IWindow.h"
#include "../Platform/GLFWWindow.h"
#include "../Platform/Input.h"
#include "../Graphics/CubeRenderer.h"

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

    void Application::update()
    {
        // Timers, Events, Input polling
    }

    int Application::run(int argc, char **argv)
    {
        if (!init(argc, argv))
            return -1;

        GLFWWindow window;
        WindowDesc wd;
        wd.width = config().get().windowWidth;
        wd.height = config().get().windowHeight;
        wd.title = config().get().windowTitle.c_str();
        wd.vsync = config().get().vsync;

        if (!window.create(wd))
            return 1;

        window.setCloseCallback([&]()
                                { requestQuit(); });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            return 1;
        }

        Input input(window.nativeHandle());

        CubeRenderer _testRenderer;

        while (_running && !window.shouldClose())
        {
            _clock->tick();
            window.pollEvents();

            update();

            // Renderer calls.
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            // Clear both color and depth each frame to avoid stale depth values
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render test cube at origin so it's inside clip space for the simple shader
            _testRenderer.renderCube(glm::vec3(0.0f));

            window.swapBuffers();
        }

        shutdown();
        return 0;
    }
}