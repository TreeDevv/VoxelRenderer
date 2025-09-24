#include "Application.h"
#include "EngineConfig.h"
#include "Clock.h"
#include "../Platform/IWindow.h"
#include "../Platform/GLFWWindow.h"
#include "../Graphics/GLRenderer.h"

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

        GLRenderer renderer(window);
        renderer.initialize();

        while (_running && !window.shouldClose())
        {
            _clock->tick();
            window.pollEvents();

            update();

            // Renderer calls.
            renderer.beginFrame();
            renderer.draw();
            renderer.endFrame();

            window.swapBuffers();
        }

        shutdown();
        return 0;
    }
}