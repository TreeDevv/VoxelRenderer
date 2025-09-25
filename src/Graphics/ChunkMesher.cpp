#include "ChunkMesher.h"

#include "glad.h"

GameGraphics::ChunkMesher::ChunkMesher(Chunk &chunk)
    : _chunk(chunk) // initialize member variable(s) here
{
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ibo);
}

void GameGraphics::ChunkMesher::generateFaces()
{
}

void GameGraphics::ChunkMesher::draw()
{
}
