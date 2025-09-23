#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

#include <string>

namespace GameCore
{
    struct EngineConfigData {
        int windowWidth = 1280;
        int windowHeight = 720;
        bool vsync = true;
        std::string windowTitle = "BlockGame";
        std::string assetsDir = "assets";
        std::string shadersDir = "assets/shaders";
        std::string savesDir = "saves";
    };

    class EngineConfig
    {
    public:
        void loadFromFile(const std::string& path);

        const EngineConfigData& get() const { return _data; }
        EngineConfigData& mutate() { return _data; } // For mutable settings
    private:
        EngineConfigData _data;
    };
}

#endif