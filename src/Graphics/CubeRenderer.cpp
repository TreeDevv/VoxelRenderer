#include "CubeRenderer.h"

GameGraphics::CubeRenderer::CubeRenderer()
{
    _vao = VertexArray();
    _vbo = VertexBuffer();

    _vao.Bind();
    
    _vbo.Bind();
    // _vbo.BufferData();

    _vbo.Unbind();
    _vao.Unbind();
}

GameGraphics::CubeRenderer::~CubeRenderer()
{
}

void GameGraphics::CubeRenderer::renderCube(const glm::vec3 &position)
{
    _vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    _vao.Unbind();
}
