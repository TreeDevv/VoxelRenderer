#pragma once

#include <glad/glad.h>

class IndexBuffer
{
    public:
    IndexBuffer()
    {
        glGenBuffers(1, &handle);
    };

    void BufferData(GLsizei size, void* data, GLenum usage)
    {
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    };

    void Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    };
    
    void Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    };

    private:
    GLuint handle;
};