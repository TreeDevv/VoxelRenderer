#include "Chunk.h"
#include "../Graphics/ChunkMesh.h"

std::unordered_map<glm::vec2, std::shared_ptr<GameWorld::Chunk>> GameWorld::Chunk::GameChunks;

namespace GameWorld
{

    std::shared_ptr<GameGraphics::ChunkMesh> Chunk::getMesh()
    {
        // If mesh doesn't exist or chunk is dirty, create/regenerate the mesh
        if (!_mesh || _dirty)
        {
            _mesh = std::make_shared<GameGraphics::ChunkMesh>(shared_from_this());
            _mesh->constructMesh();
            _dirty = false;
        }
        return _mesh;
    }
}
