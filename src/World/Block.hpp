#pragma once

#include "../Util/util.hpp"
#include <unordered_map>
#include <glm/glm.hpp>

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
        virtual glm::ivec2 textureOffset(Util::Direction face) const {
            std::cout << "Trying to use default block. Please overload textureOffset member\n";
            return glm::vec2(0);
        };
        bool transparent;
    };

    struct Air : Block {
        BlockID id = BlockID::AIR;
        bool transparent = true;
    };

    struct Grass : Block {
        BlockID id = BlockID::GRASS;
        glm::ivec2 textureOffset(Util::Direction face) const override {
            switch(face) {
                case Util::Direction::Top:
                    return glm::ivec2(0, 0);
                case Util::Direction::Bottom:
                    return glm::ivec2(2, 0);
                default:
                    return glm::ivec2(1, 0);
            }
        }
        bool transparent = false;
    };

    struct Dirt : Block {
        BlockID id = BlockID::DIRT;
        glm::ivec2 textureOffset(Util::Direction face) const override { return glm::ivec2(0, 2); }
        bool transparent = false;
    };

    static const std::unordered_map<BlockID, Block> BlockIndex = {
        {BlockID::AIR, Air()},
        {BlockID::GRASS, Grass()},
        {BlockID::DIRT, Dirt()},
    };
}