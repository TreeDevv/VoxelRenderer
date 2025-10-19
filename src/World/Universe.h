#pragma once

#include "Chunk.h"

#include <glm.hpp>
#include <unordered_map>
#include <memory>

namespace GameWorld
{
    class Universe
    {
    public:
        void update(glm::vec3 playerPos);

    private:
        std::shared_ptr<std::unordered_map<glm::vec2, std::shared_ptr<Chunk>>> _renderDistance;
    };
}
