#include "Chunk.h"
#include "../Graphics/ChunkMesh.h"

namespace GameWorld
{

    std::shared_ptr<GameGraphics::ChunkMesh> Chunk::getMesh(std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> &renderDistance)
    {
        // If mesh doesn't exist or chunk is dirty, create/regenerate the mesh
        if (!_mesh)
        {
            _mesh = std::make_shared<GameGraphics::ChunkMesh>(shared_from_this());
        }
        if (_dirty)
        {
            _mesh->constructMesh(renderDistance);
            _dirty = false;
        }
        return _mesh;
    }
}
