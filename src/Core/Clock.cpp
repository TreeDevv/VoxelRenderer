#include "Clock.h"
#include <chrono>

using namespace GameCore;

namespace GameCore
{

    void GameCore::Clock::tick()
    {
        static bool first = true;
        auto now = std::chrono::steady_clock::now();
        auto now_us = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();

        if (first)
        {
            _lastTicks = static_cast<std::uint64_t>(now_us);
            first = false;
            _dt = 0.0;
        }
        else
        {
            auto last = _lastTicks;
            _lastTicks = static_cast<std::uint64_t>(now_us);
            _dt = double(_lastTicks - last) / 1'000'000.0;
        }
        _elapsed += _dt;
    }
}