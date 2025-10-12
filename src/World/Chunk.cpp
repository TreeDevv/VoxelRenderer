#include "Chunk.h"
#include "../Graphics/ChunkMesh.h"

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
