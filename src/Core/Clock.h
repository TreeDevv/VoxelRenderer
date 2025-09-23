#ifndef CLOCK_H
#define CLOCK_H

#include <cstdint>

namespace GameCore
{

class Clock
{
    public:
        void tick(); // once per frame
        double deltaSeconds() const { return _dt; }
        double elapsedSeconds() const { return _elapsed; }

    private:
        double _dt = 0.0;
        double _elapsed = 0.0;
        std::uint64_t _lastTicks = 0;
};

}

#endif