#include "CubeRenderer.h"

GameGraphics::CubeRenderer::CubeRenderer() : _defaultProgram("assets/shaders/BasicVert.glsl", "assets/shaders/BasicFrag.glsl")
{
    float vertices[] = {

            // back face
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            // front face
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            // left
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            // right
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

             // bottom
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            // top
            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
        };

    _vao.Bind();
    
    _vbo.Bind();
    _vbo.BufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    _vbo.VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    _vbo.Unbind();
    _vao.Unbind();
}

GameGraphics::CubeRenderer::~CubeRenderer()
{
}

void GameGraphics::CubeRenderer::renderCube(std::shared_ptr<Camera> camera, const glm::vec3 &position)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

    _defaultProgram.use();
    _defaultProgram.setMat4("u_Model", model);
    _defaultProgram.setMat4("u_View", camera->GetViewMatrix());
    _defaultProgram.setMat4("u_Projection", camera->GetPerspectiveMatrix());

    // _vao.Bind();
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // _vao.Unbind();
}
