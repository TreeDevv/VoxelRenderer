#include <iostream>

namespace Util {
    const static uint16_t TEXTURE_SIZE = 16;

    enum class Direction : uint8_t
        {
            Right = 0,
            Left = 1,
            Top = 2,
            Bottom = 3,
            Front = 4,
            Back = 5,
    }; // +X -X +Y
}
