#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Block/Block.h"

// Forward declaration to avoid circular includes
namespace GameGraphics
{
    class ChunkMesh;
}

namespace GameWorld
{
    class Chunk : public std::enable_shared_from_this<Chunk>
    {
    public:
        static constexpr int WIDTH = 16;
        static constexpr int HEIGHT = 256;
        static constexpr int LENGTH = 16;

        Chunk(glm::vec2 pos)
        {
            _pos = pos;
            _voxels.resize(WIDTH * HEIGHT * LENGTH, BlockID::AIR);
        }

        std::vector<BlockID> get() const
        {
            return _voxels;
        }

        BlockID get(int x, int y, int z) const
        {
            return _voxels[index(x, y, z)];
        }

        glm::vec2 getPos() const
        {
            return _pos * glm::vec2(WIDTH, LENGTH);
        }

        void set(int x, int y, int z, BlockID id)
        {
            _voxels[index(x, y, z)] = id;
            _dirty = true;
        }

        bool isDirty() const { return _dirty; }

        void clearDirty()
        {
            _dirty = false;
        }

        // Get the mesh for this chunk, generating it if dirty
        std::shared_ptr<GameGraphics::ChunkMesh> getMesh();

    private:
        glm::vec2 _pos;

        std::vector<BlockID> _voxels;
        bool _dirty = true;
        std::shared_ptr<GameGraphics::ChunkMesh> _mesh;

        inline int
        index(int x, int y, int z) const
        {
            return x + WIDTH * (z + LENGTH * y);
        }
    };
}