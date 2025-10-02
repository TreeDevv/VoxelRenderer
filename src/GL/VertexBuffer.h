#pragma once

#include <glad/glad.h>

class VertexBuffer
{
    public:
        VertexBuffer();
        ~VertexBuffer();
        
        void BufferData(GLsizei size, void* data, GLenum usage);

        void Bind();
        void Unbind();

        void VertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
    private:
        GLuint _vbo;
        GLenum _type;
};