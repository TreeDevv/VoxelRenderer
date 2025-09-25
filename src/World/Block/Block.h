#pragma once

namespace GameWorld
{
    enum BlockID
    {
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