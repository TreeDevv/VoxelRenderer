#include "GLRenderer.h"
#include <glad/glad.h>

bool GameGraphics::GLRenderer::initialize()
{

    return true;
}

void GameGraphics::GLRenderer::resize(int w, int h)
{
}

void GameGraphics::GLRenderer::beginFrame()
{
    glClearColor(0.3f, 0.2f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameGraphics::GLRenderer::setCamera(Camera &camera)
{
}

void GameGraphics::GLRenderer::draw()
{
}

void GameGraphics::GLRenderer::endFrame()
{
}
