#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

class Texture
{
public:
    Texture(const char *path);

    void bind();
    void unbind();

    int getWidth() const;
    int getHeight() const;

    glm::ivec2 getDimensions() const;

private:
    glm::ivec2 _dimensions;
    unsigned int _handle;
};