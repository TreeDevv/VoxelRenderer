#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_vao);
}

VertexArray::~VertexArray()
{
}

void VertexArray::Bind()
{  
    glBindVertexArray(_vao);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}
