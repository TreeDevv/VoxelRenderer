#pragma once

#include "../Util/util.hpp"

#include <unordered_map>
#include <memory>

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
        virtual glm::ivec2 textureOffset(Util::Face face) const
        {
            std::cout << "Trying to use default block. Please overload textureOffset member\n";
            return glm::vec2(0);
        };
        bool transparent;
    };

    struct Air : Block
    {
        BlockID id = BlockID::AIR;
        bool transparent = true;
    };

    struct Grass : Block
    {
        BlockID id = BlockID::GRASS;
        glm::ivec2 textureOffset(Util::Face face) const override
        {
            switch (face)
            {
            case Util::Face::PY:
                return glm::ivec2(0, 0);
            case Util::Face::NY:
                return glm::ivec2(2, 0);
            default:
                return glm::ivec2(1, 0);
            }
        }
        bool transparent = false;
    };

    struct Dirt : Block
    {
        BlockID id = BlockID::DIRT;
        glm::ivec2 textureOffset(Util::Face face) const override { return glm::ivec2(2, 0); }
        bool transparent = false;
    };

    static std::unordered_map<BlockID, std::shared_ptr<Block>> BlockIndex = {
        {BlockID::AIR, std::make_shared<Air>()},
        {BlockID::GRASS, std::make_shared<Grass>()},
        {BlockID::DIRT, std::make_shared<Dirt>()},
    };
}