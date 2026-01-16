#pragma once

#include <glad/glad.h>
#include <filesystem>

class Texture {
public:
    unsigned int ID;

    Texture(const std::filesystem::path texturePath, GLenum textureUnit, GLenum textureFormat);

    void bind();
};

