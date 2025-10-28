#include "ChunkGenerator.h"

void GameWorld::ChunkGenerator::generate(std::shared_ptr<Chunk> chunk)
{
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 128; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                if (y < x * 0.5f + 4)
                {
                    chunk->set(x, y, z, BlockID::DIRT);
                }
            }
        }
    }
}