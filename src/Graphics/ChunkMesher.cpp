#include "ChunkMesher.h"

GameGraphics::ChunkMesher::ChunkMesher(Chunk &chunk)
    : _chunk(chunk) // initialize member variable(s) here
{
    _vao = VertexArray();
    _vbo = VertexBuffer();
}

void GameGraphics::ChunkMesher::generateFaces()
{
}