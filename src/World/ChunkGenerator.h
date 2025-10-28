#pragma once

#include "Chunk.h"

using namespace GameWorld;

namespace GameWorld {
    enum class BIOME {
        TESTING,
    };

    struct ChunkGenerator {
        static void generate(std::shared_ptr<Chunk> chunk);
    };
}