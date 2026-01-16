#pragma once

#include <glad/glad.h>

class Texture {
public:
    unsigned int ID;

    Texture(const char* texturePath, GLenum textureUnit, GLenum textureFormat);

    void bind();
};

