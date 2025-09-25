#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm.hpp>
#include "Chunk.h"

using namespace GameWorld;

namespace GameGraphics
{
    struct Vertex
    {
        glm::vec3 pos; // Location 0
        glm::vec2 uv;  // Location 1
        uint8_t ao;    // Location 2
    };

    enum class Face : uint8_t
    {
        PX,
        NX,
        PY,
        NY,
        PZ,
        NZ
    }; // +X -X +Y -Y +Z -Z

    static const glm::ivec3 kFaceNormalI[6] = {
        {+1, 0, 0},
        {-1, 0, 0}, // PX, NX
        {0, +1, 0},
        {0, -1, 0}, // PY, NY
        {0, 0, +1},
        {0, 0, -1}, // PZ, NZ
    };

    class ChunkMesher
    {
    public:
        ChunkMesher(Chunk &chunk);

        void generateFaces();
        void draw();

    private:
        Chunk &_chunk;

        unsigned int _vbo;
        unsigned int _ibo;
        size_t _indicesSize;
    };
}