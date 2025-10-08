#pragma once

namespace GameWorld
{
    enum BlockID
    {
        AIR = 0,
        GRASS = 1,
        DIRT = 2,
        STONE = 3,
    };

    struct Block
    {
        BlockID id;
        bool transparent;
    };
}