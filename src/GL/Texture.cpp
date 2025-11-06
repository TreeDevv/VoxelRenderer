#include "Texture.h"

Texture::Texture(const char *path)
{
    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true); // GL tex coords start at bottom left. We want to use a top left apporach

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateTextureMipmap(GL_TEXTURE_2D);
    } else {
        throw;
    }
    _dimensions = glm::ivec2(width, height);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, _handle);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getWidth() const
{
    return _dimensions.x;
}

int Texture::getHeight() const
{
    return _dimensions.y;
}

glm::ivec2 Texture::getDimensions() const
{
    return _dimensions;
}
