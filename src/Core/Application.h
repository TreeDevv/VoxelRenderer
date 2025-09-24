#ifndef APPLICATION_H
#define APPLICATION_H

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
        void update(); // Per frame update. No rendering

        bool _running = true;

        EngineConfig *_config;
        Clock *_clock;
    };

}

#endif