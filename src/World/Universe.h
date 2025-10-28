#pragma once

#include "Chunk.h"

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include <algorithm>

namespace GameWorld
{
    const int RENDER_DISTANCE = 8;

    inline static bool inRenderDistance(glm::vec2 originPos, glm::vec2 chunkPos) {
        return (abs(originPos.x - chunkPos.x) < RENDER_DISTANCE && abs(originPos.y - chunkPos.y) < RENDER_DISTANCE);
    }

    class Universe
    {
    public:
        Universe(glm::vec3 playerPos);
        void update(glm::vec3 playerPos);

        std::unordered_map<glm::vec2, std::shared_ptr<Chunk>>& getRenderList();

    private:
        glm::vec3 _playerPos;

        std::unordered_map<glm::vec2, std::shared_ptr<GameWorld::Chunk>> _chunks;
    };
}
