#include "ChunkGenerator.h"

#include "noise.hpp"
#include <algorithm>

void GameWorld::ChunkGenerator::generate(std::shared_ptr<Chunk> chunk)
{
    const static int seed = 4;
    const static siv::PerlinNoise perlin(seed);

    for (int x = 0; x < 16; x++)
    {
        for (int z = 0; z < 16; z++)
        {
            auto chunkPos = chunk->getPos();
            double noise = perlin.octave2D_01((x + chunkPos.x) * 0.01, (z + chunkPos.y) * 0.01, 3);
            noise = floor(noise * 30);
            for (int y = 0; y < noise; y ++) {
                chunk->set(x, y, z, BlockID::DIRT);
            }
        }
    }
}