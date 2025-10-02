#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/common.hpp>

#include "../GL/VertexArray.h"
#include "../GL/VertexBuffer.h"

#include "../World/Chunk.h"

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
        PX = 0,
        NX = 1,
        PY = 2,
        NY = 3,
        PZ = 4,
        NZ = 5,
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
        
        VertexArray getVAO() const { return _vao; }

        private:
        Chunk &_chunk;
        
        VertexArray _vao;
        VertexBuffer _vbo;
    };
}