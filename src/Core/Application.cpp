#include <Application.h>
#include <EngineConfig.h>
#include <Clock.h>

using namespace GameCore;

Application::Application() = default;
Application::~Application() {
    shutdown(); 
    
    delete _clock;
    delete _config;
}

bool Application::init(int argc, char** argv)
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

int Application::run(int argc, char** argv)
{
    if (!init(argc, argv)) return -1;

    while (_running)
    {
        _clock->tick();

        update();

        // Renderer calls.
    }

    shutdown();
    return 0;
}