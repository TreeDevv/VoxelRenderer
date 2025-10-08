#pragma once

#include <vector>
#include "Block/Block.h"

namespace GameWorld
{
    class Chunk
    {
    public:
        static constexpr int WIDTH = 16;
        static constexpr int HEIGHT = 256;
        static constexpr int LENGTH = 16;

        Chunk()
        {
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

    private:
        std::vector<BlockID> _voxels;
        bool _dirty = true;

        inline int
        index(int x, int y, int z) const
        {
            return x + WIDTH * (z + LENGTH * y);
        }
    };
}