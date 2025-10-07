#ifndef APPLICATION_H
#define APPLICATION_H

#include "Services.h"
#include <memory>

namespace GameCore
{

    class EngineConfig;
    class Clock;

    class Application
    {
    public:
        Application();
        ~Application();

        int run(int argc, char **argv);

        // higher layers can call down to this
        void requestQuit() { _running = false; }

        EngineConfig &config() const { return *_config; }
        Clock &clock() const { return *_clock; }

    private:
        bool init(int argc, char **argv);
        void shutdown();
        void update(std::shared_ptr<Services> services); // Per frame update. No rendering

        bool _running = true;

        EngineConfig *_config;
        Clock *_clock;
    };

}

#endif