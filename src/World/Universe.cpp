#include "Universe.h"

#include <exception>
#include <iostream>
#include "ChunkGenerator.h"

using namespace GameWorld;

GameWorld::Universe::Universe(glm::vec3 playerPos) : _playerPos(playerPos)
{
}

void GameWorld::Universe::update(glm::vec3 playerPos)
{
    // Calculate render distance and generate chunks
    glm::vec2 currentChunk = glm::ivec2(playerPos.x / 16, playerPos.z / 16);
    const glm::vec2
        minOffset = currentChunk - glm::vec2(RENDER_DISTANCE, RENDER_DISTANCE),
        maxOffset = currentChunk + glm::vec2(RENDER_DISTANCE, RENDER_DISTANCE);

    // Get rid of chunks not in range
    // TODO: Cache chunk data
    for (auto it = _chunks.begin(); it != _chunks.end();)
    {
        auto &[pos, chunk] = *it;
        if (pos.x < minOffset.x || pos.x > maxOffset.x || pos.y < minOffset.y || pos.y > maxOffset.y)
        {
            this->_chunks.erase(it++);
        }
        else
        {
            it++;
        }
    }

    for (int x = minOffset.x; x < maxOffset.x; x++)
    {
        for (int y = minOffset.y; y < maxOffset.y; y++)
        {
            glm::vec2 pos(x, y);

            if (!this->_chunks.contains(pos))
            {
                // Generate chunk
                auto chunk = std::make_shared<Chunk>(pos);
                this->_chunks.emplace(pos, chunk);
                ChunkGenerator::generate(chunk);
            }
        }
    }
}

std::unordered_map<glm::vec2, std::shared_ptr<GameWorld::Chunk>> &GameWorld::Universe::getRenderList()
{
    return _chunks;
}
