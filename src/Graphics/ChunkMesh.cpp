#include "ChunkMesh.h"

#include <iostream>

GameGraphics::ChunkMesh::ChunkMesh(std::shared_ptr<Chunk> chunk)
    : _chunk(chunk) // initialize member variable(s) here
{
    static bool IndexBufferInitialized = false;
    static IndexBuffer StaticIBO;
    if (!IndexBufferInitialized)
    {
        GLuint* IndexBuffer = nullptr;

        int indexSize = chunk->WIDTH * chunk->HEIGHT * chunk->WIDTH * 6; 
        int indexOffset = 0;

        IndexBuffer = new GLuint[indexSize * 6];

        for (size_t i = 0; i < indexSize; i += 6)
        {
            IndexBuffer[i]     = 0 + indexOffset;
            IndexBuffer[i + 1] = 1 + indexOffset;
            IndexBuffer[i + 2] = 2 + indexOffset;
            IndexBuffer[i + 3] = 2 + indexOffset;
            IndexBuffer[i + 4] = 3 + indexOffset;
            IndexBuffer[i + 5] = 0 + indexOffset;

            indexOffset = indexOffset + 4;
        }

        StaticIBO.BufferData(indexSize * 6 * sizeof(GLuint), IndexBuffer, GL_STATIC_DRAW);
        delete[] IndexBuffer;

        IndexBufferInitialized = true;
    }

    _vao = VertexArray();
    _vbo = VertexBuffer();
    
    _vao.Bind();
    _vbo.Bind();
    StaticIBO.Bind();
   _vbo.VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
   _vao.Unbind();
}

void GameGraphics::ChunkMesh::constructMesh()
{
    for (int x = 0; x < _chunk->WIDTH; x++)
    {
        for (int y = 0; y < _chunk->HEIGHT; y++)
        {
            for (int z = 0; z < _chunk->LENGTH; z++)
            {
                if (
                    x == 0 ||
                    x >= _chunk->WIDTH - 1 ||
                    y == 0 ||
                    y >= _chunk->HEIGHT - 1 ||
                    z == 0 ||
                    z >= _chunk->LENGTH - 1
                ) // Edge of chunk condition. For now emit nothing to test
                {
                    continue;
                }

                // TODO Index block id for now just check air 0
                // Check all sides for blocks
                if (_chunk->get(x + 1, y, z) == 0) // Right face
                {
                    _addFace(glm::vec3(x, y, z), Face::PX);
                }
                if (_chunk->get(x - 1, y, z) == 0) // Left face
                {
                    _addFace(glm::vec3(x, y, z), Face::NX);
                }
                if (_chunk->get(x, y + 1, z) == 0) // Top face
                {
                    _addFace(glm::vec3(x, y, z), Face::PY);
                }
                if (_chunk->get(x, y - 1, z) == 0) // Bottom face
                {
                    _addFace(glm::vec3(x, y, z), Face::NY);
                }
                if (_chunk->get(x, y, z + 1) == 0) // Front face
                {
                    _addFace(glm::vec3(x, y, z), Face::PZ);
                }
                if (_chunk->get(x, y, z - 1) == 0) // Front face
                {
                    _addFace(glm::vec3(x, y, z), Face::NZ);
                }
            }
        }
    }

    if (m_Vertices.size() > 0)
    {
        _vbo.BufferData(m_Vertices.size() * sizeof(Vertex), &m_Vertices.front(), GL_STATIC_DRAW);
        _verticesCount = m_Vertices.size();
        m_Vertices.clear();
    }
    else
    {
        std::cout << "No vertices";
    }
}

void GameGraphics::ChunkMesh::_addFace(glm::vec3 position, Face face)
{
    // Each face is 4 vertices 
    Vertex v1, v2, v3, v4;
    v1.pos = position + kFaces[(int)face][0];
    v2.pos = position + kFaces[(int)face][1];
    v3.pos = position + kFaces[(int)face][2];
    v4.pos = position + kFaces[(int)face][3];
    
    m_Vertices.push_back(v1);
    m_Vertices.push_back(v2);
    m_Vertices.push_back(v3);
    m_Vertices.push_back(v4);
}
