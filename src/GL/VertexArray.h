#pragma once

#include <glad/glad.h>

class VertexArray
{
    public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    private:
    GLuint _vao;
};