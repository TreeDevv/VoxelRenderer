#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

class Texture {
public:
    Texture(const char* path);

    void bind();
    void unbind();

    int getWidth() const noexcept;
    int getHeight() const noexcept;

    glm::ivec2 getDimensions() const noexcept;
private:
    glm::ivec2 _dimensions;
    unsigned int _handle;
};