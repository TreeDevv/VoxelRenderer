#pragma once

#include <iostream>

namespace Util
{
    constexpr uint16_t TEXTURE_SIZE = 16;

    enum class Face : uint8_t
    {
        PX = 0,
        NX = 1,
        PY = 2,
        NY = 3,
        PZ = 4,
        NZ = 5,
    }; // +X -X +Y -Y +Z -Z

}
