#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/common.hpp>

#include "../GL/IndexBuffer.hpp"
#include "../GL/VertexArray.h"
#include "../GL/VertexBuffer.h"

#include "../World/Chunk.h"

using namespace GameWorld;

namespace GameGraphics
{
    struct Vertex
    {
        glm::vec3 pos; // Location 0
        uint8_t ao;
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

    static const glm::vec3 kFaces[6][4] = {
        {
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 1.0f},
        }, // PX
        {
            {0.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f},
        }, // NX
        {
            {0.0f, 1.0f, 0.0f},
            {1.0f, 1.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 1.0f},
        }, // PY
        {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},
        }, // NY
        {
            {0.0f, 0.0f, 1.0f},
            {1.0f, 0.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 1.0f},
        }, // PZ
        {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
        } // NZ
    };

    static const glm::vec3 kVertexNeighbors[6][4][3] = {
        // --- PX (+X face) ---
        {
            {{0, -1, 0}, {0, 0, -1}, {0, -1, -1}}, // v0 (1,1,1)
            {{0, 1, 0}, {0, 0, -1}, {0, 1, -1}},   // v1 (1,1,0)
            {{0, 1, 0}, {0, 0, 1}, {0, 1, 1}},     // v2 (1,0,0)
            {{0, -1, 0}, {0, 0, 1}, {0, -1, 1}},   // v3 (1,0,1)
        },
        // --- NX (-X face) ---
        {
            {{0, -1, 0}, {0, 0, -1}, {0, -1, -1}}, // v0 (0,1,1)
            {{0, 1, 0}, {0, 0, -1}, {0, 1, -1}},   // v1 (0,1,0)
            {{0, 1, 0}, {0, 0, 1}, {0, 1, 1}},     // v2 (0,0,0)
            {{0, -1, 0}, {0, 0, 1}, {0, -1, 1}},   // v3 (0,0,1)
        },
        // --- PY (+Y face) ---
        {
            {{-1, 0, 0}, {0, 0, -1}, {-1, 0, -1}}, // v0 (0,1,0)
            {{1, 0, 0}, {0, 0, -1}, {1, 0, -1}},   // v1 (1,1,0)
            {{1, 0, 0}, {0, 0, 1}, {1, 0, 1}},     // v2 (1,1,1)
            {{-1, 0, 0}, {0, 0, 1}, {-1, 0, 1}},   // v3 (0,1,1)
        },
        // --- NY (-Y face) ---
        {
            {{-1, 0, 0}, {0, 0, -1}, {-1, 0, -1}}, // v0 (0,0,0)
            {{1, 0, 0}, {0, 0, -1}, {1, 0, -1}},   // v1 (1,0,0)
            {{1, 0, 0}, {0, 0, 1}, {1, 0, 1}},     // v2 (1,0,1)
            {{-1, 0, 0}, {0, 0, 1}, {-1, 0, 1}},   // v3 (0,0,1)
        },
        // --- PZ (+Z face) ---
        {
            {{-1, 0, 0}, {0, -1, 0}, {-1, -1, 0}}, // v0 (0,0,1)
            {{1, 0, 0}, {0, -1, 0}, {1, -1, 0}},   // v1 (1,0,1)
            {{1, 0, 0}, {0, 1, 0}, {1, 1, 0}},     // v2 (1,1,1)
            {{-1, 0, 0}, {0, 1, 0}, {-1, 1, 0}},   // v3 (0,1,1)
        },
        // --- NZ (-Z face) ---
        {
            {{-1, 0, 0}, {0, -1, 0}, {-1, -1, 0}}, // v0 (0,0,0)
            {{1, 0, 0}, {0, -1, 0}, {1, -1, 0}},   // v1 (1,0,0)
            {{1, 0, 0}, {0, 1, 0}, {1, 1, 0}},     // v2 (1,1,0)
            {{-1, 0, 0}, {0, 1, 0}, {-1, 1, 0}},   // v3 (0,1,0)
        }};

    class ChunkMesh
    {
    public:
        ChunkMesh(std::shared_ptr<Chunk> chunk);

        void constructMesh(std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData);

        VertexArray getVAO() const { return _vao; }
        unsigned int getVerticeCount() const { return _verticesCount; }

    private:
        std::shared_ptr<Chunk> _chunk;

        VertexArray _vao;
        VertexBuffer _vbo;

        std::vector<Vertex> m_Vertices;
        unsigned int _verticesCount;

        void _addFace(glm::vec3 position, Face face, std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData);
        int _calculateAoValue(glm::vec3 pos, Face face, int vert, std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData);

        bool renderDataIsOpaque(glm::vec3 localPos, std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData);
    };
}