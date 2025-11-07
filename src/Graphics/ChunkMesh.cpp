#include "ChunkMesh.h"

#include <iostream>

using namespace Util;

GameGraphics::ChunkMesh::ChunkMesh(std::shared_ptr<Chunk> chunk)
    : _chunk(chunk) // initialize member variable(s) here
{
    static bool IndexBufferInitialized = false;
    static IndexBuffer StaticIBO;
    if (!IndexBufferInitialized)
    {
        GLuint *IndexBuffer = nullptr;

        int indexSize = chunk->WIDTH * chunk->HEIGHT * chunk->WIDTH * 6;
        int indexOffset = 0;

        IndexBuffer = new GLuint[indexSize * 6];

        for (size_t i = 0; i < indexSize; i += 6)
        {
            IndexBuffer[i] = 0 + indexOffset;
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

    _vbo.VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
    _vbo.VertexAttribute(1, 1, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, ao));
    _vbo.VertexAttribute(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    _vbo.VertexAttribute(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texPos));

    _vao.Unbind();
}

void GameGraphics::ChunkMesh::constructMesh(std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData)
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
                    z >= _chunk->LENGTH - 1) // Edge of chunk condition. For now emit all to test
                {
                    // if (_chunk->isSolid(glm::vec3(x, y, z)))
                    // {
                    //     _addFace(glm::vec3(x, y, z), Face::PX);
                    //     _addFace(glm::vec3(x, y, z), Face::NX);
                    //     _addFace(glm::vec3(x, y, z), Face::PY);
                    //     _addFace(glm::vec3(x, y, z), Face::NY);
                    //     _addFace(glm::vec3(x, y, z), Face::PZ);
                    //     _addFace(glm::vec3(x, y, z), Face::NZ);
                    //     continue;
                    // }
                }

                // TODO Index block id for now just check air 0
                // Check all sides for blocks
                if (!renderDataIsOpaque(glm::vec3(x, y, z), renderData))
                    continue;
                if (!renderDataIsOpaque(glm::vec3(x + 1, y, z), renderData)) // Right face
                {
                    _addFace(glm::vec3(x, y, z), Face::PX, renderData);
                }
                if (!renderDataIsOpaque(glm::vec3(x - 1, y, z), renderData)) // Left face
                {
                    _addFace(glm::vec3(x, y, z), Face::NX, renderData);
                }
                if (!renderDataIsOpaque(glm::vec3(x, y + 1, z), renderData)) // Top face
                {
                    _addFace(glm::vec3(x, y, z), Face::PY, renderData);
                }
                if (!renderDataIsOpaque(glm::vec3(x, y - 1, z), renderData)) // Bottom face
                {
                    _addFace(glm::vec3(x, y, z), Face::NY, renderData);
                }
                if (!renderDataIsOpaque(glm::vec3(x, y, z + 1), renderData)) // Front face
                {
                    _addFace(glm::vec3(x, y, z), Face::PZ, renderData);
                }
                if (!renderDataIsOpaque(glm::vec3(x, y, z - 1), renderData)) // Front face
                {
                    _addFace(glm::vec3(x, y, z), Face::NZ, renderData);
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
        // std::cout << "No vertices";
    }
}

void GameGraphics::ChunkMesh::_addFace(glm::vec3 position, Face face, std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData)
{
    BlockID currentBlock = this->_chunk->get(position);
    auto &blockInfo = BlockIndex.at(currentBlock);

    glm::ivec2 textureOffset = blockInfo->textureOffset(face);
    glm::ivec2 textureOffsetPixels = textureOffset * glm::ivec2(16, 16);

    // Each face is 4 vertices //TODO CALCULATE AO HERE
    Vertex v1, v2, v3, v4;
    v1.pos = position + kFaces[(int)face][0];
    v1.ao = _calculateAoValue(position, face, 0, renderData);
    v1.normal = kFaceNormalI[(int)face];
    v1.texPos = glm::vec2(textureOffsetPixels.x, textureOffsetPixels.y);

    v2.pos = position + kFaces[(int)face][1];
    v2.ao = _calculateAoValue(position, face, 1, renderData);
    v2.normal = kFaceNormalI[(int)face];
    v2.texPos = glm::vec2(textureOffsetPixels.x + 16, textureOffsetPixels.y);

    v3.pos = position + kFaces[(int)face][2];
    v3.ao = _calculateAoValue(position, face, 2, renderData);
    v3.normal = kFaceNormalI[(int)face];
    v3.texPos = glm::vec2(textureOffsetPixels.x + 16, textureOffsetPixels.y + 16);

    v4.pos = position + kFaces[(int)face][3];
    v4.ao = _calculateAoValue(position, face, 3, renderData);
    v4.normal = kFaceNormalI[(int)face];
    v4.texPos = glm::vec2(textureOffsetPixels.x, textureOffsetPixels.y + 16);
    // Convert pixel position to normalized versions in frag shader

    // std::cout << "UVs: "
    //           << v1.texPos.x << "," << v1.texPos.y << "  |  "
    //           << v2.texPos.x << "," << v2.texPos.y << "  |  "
    //           << v3.texPos.x << "," << v3.texPos.y << "  |  "
    //           << v4.texPos.x << "," << v4.texPos.y << "\n";

    m_Vertices.push_back(v1);
    m_Vertices.push_back(v2);
    m_Vertices.push_back(v3);
    m_Vertices.push_back(v4);
}

int GameGraphics::ChunkMesh::_calculateAoValue(glm::vec3 pos, Face face, int vert, std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData)
{
    bool s1 = renderDataIsOpaque(pos + kVertexNeighbors[(int)face][vert][0], renderData);
    bool s2 = renderDataIsOpaque(pos + kVertexNeighbors[(int)face][vert][1], renderData);
    bool s3 = renderDataIsOpaque(pos + kVertexNeighbors[(int)face][vert][2], renderData);

    if (s1 && s2)
        return 3;
    else
        return (int)s1 + (int)s2 + (int)s3;
}

bool GameGraphics::ChunkMesh::renderDataIsOpaque(glm::vec3 localPos, std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderData)
{

    // Add to offset
    // Corner conditions
    if (localPos.x < Chunk::WIDTH && localPos.x >= 0 && localPos.y >= 0 && localPos.y < Chunk::HEIGHT && localPos.z >= 0 && localPos.z < Chunk::LENGTH)
    {
        return this->_chunk->get(localPos) != 0;
    }

    if (localPos.y >= Chunk::HEIGHT || localPos.y < 0)
        return false; // No vertical chunking so y case visible is false
    if (localPos.x < 0 && localPos.z < 0)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x - 1, _chunk->getPos().y - 1);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(Chunk::WIDTH, localPos.y, Chunk::LENGTH) != 0;
    }
    else if (localPos.x < 0 && localPos.z >= Chunk::LENGTH)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x - 1, _chunk->getPos().y + 1);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(Chunk::Chunk::WIDTH, localPos.y, 0) != 0;
    }
    else if (localPos.x >= Chunk::Chunk::WIDTH && localPos.z < 0)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x + 1, _chunk->getPos().y - 1);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(0, localPos.y, Chunk::LENGTH) != 0;
    }
    else if (localPos.x >= Chunk::Chunk::WIDTH && localPos.z >= Chunk::LENGTH)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x + 1, _chunk->getPos().y - 1);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(0, localPos.y, 0) != 0;
    }
    // One chunk over conditions
    if (localPos.x < 0)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x - 1, _chunk->getPos().y);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(Chunk::Chunk::WIDTH, localPos.y, localPos.z) != 0;
    }
    else if (localPos.x >= Chunk::Chunk::WIDTH)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x + 1, _chunk->getPos().y);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(0, localPos.y, localPos.z) != 0;
    }
    else if (localPos.z < 0)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x, _chunk->getPos().y - 1);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(localPos.x, localPos.y, Chunk::LENGTH) != 0;
    }
    else if (localPos.z >= Chunk::LENGTH)
    {
        glm::vec2 index = glm::vec2(_chunk->getPos().x, _chunk->getPos().y + 1);
        if (renderData.find(index) == renderData.end())
            return false;
        return renderData[index]->get(localPos.x, localPos.y, 0) != 0;
    }
    return false;
}
