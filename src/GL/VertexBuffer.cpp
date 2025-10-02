#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &_vbo);
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::BufferData(GLsizei size, void *data, GLenum usage)
{
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::VertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
{   
    // Last arg is first appearence offset
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}
