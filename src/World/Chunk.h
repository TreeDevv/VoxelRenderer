#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>
#include "Block/Block.h"

// Forward declaration to avoid circular includes
namespace GameGraphics
{
    class ChunkMesh;
}

// hash vec2 to hold onto chunk references
template<>
struct std::hash<glm::vec2> {
    size_t operator()(const glm::vec2& v) const noexcept {
            size_t h1 = hash<float>{}(v.x);
            size_t h2 = hash<float>{}(v.y);
            return h1 ^ (h2 << 1);
        }
};

namespace GameWorld
{
    class Chunk : public std::enable_shared_from_this<Chunk>
    {
    public:
        static std::unordered_map<glm::vec2, std::shared_ptr<Chunk>> GameChunks;

        static constexpr int WIDTH = 16;
        static constexpr int HEIGHT = 256;
        static constexpr int LENGTH = 16;

        Chunk(glm::vec2 pos)
        {
            _pos = pos;
            _voxels.resize(WIDTH * HEIGHT * LENGTH, BlockID::AIR);

            GameChunks[pos] = shared_from_this();
        }

        std::vector<BlockID> get() const
        {
            return _voxels;
        }

        BlockID get(glm::vec3 pos) const
        {
            // Corner conditions
            if (pos.x < 0 && pos.z < 0) {
                return GameChunks[glm::vec2(_pos.x - 1, _pos.y - 1)]->get(WIDTH, pos.y, LENGTH);
            } else if (pos.x < 0 && pos.z > LENGTH) {
                return GameChunks[glm::vec2(_pos.x - 1, _pos.y + 1)]->get(WIDTH, pos.y, 0);
            } else if (pos.x > WIDTH && pos.z < 0) {
                return GameChunks[glm::vec2(_pos.x + 1, _pos.y - 1)]->get(0, pos.y, LENGTH);
            } else if (pos.x > WIDTH && pos.z > LENGTH) {
                return GameChunks[glm::vec2(_pos.x + 1, _pos.y - 1)]->get(0, pos.y, 0);
            }
            // One chunk over conditions
            if (pos.x < 0) {
                return GameChunks[glm::vec2(_pos.x - 1, _pos.y)]->get(WIDTH, pos.y, pos.z);
            } else if (pos.x > WIDTH) {
                return GameChunks[glm::vec2(_pos.x + 1, _pos.y)]->get(0, pos.y, pos.z);
            } else if (pos.z < 0) {
                return GameChunks[glm::vec2(_pos.x, _pos.y - 1)]->get(pos.x, pos.y, LENGTH);
            } else if(pos.z > LENGTH) {
                return GameChunks[glm::vec2(_pos.x, _pos.y + 1)]->get(pos.x, pos.y, 0);
            }
            
            return get(pos.x, pos.y, pos.z);
        }

        BlockID get(int x, int y, int z) const
        {
            return _voxels[index(x, y, z)];
        }

        bool isSolid(glm::vec3 pos) const 
        {
            return (get(pos) == BlockID::AIR);
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