#pragma once

#include <glad/glad.h>
#include <filesystem>

class Texture {
public:
    unsigned int ID;

    Texture(const std::filesystem::path texturePath, const GLenum textureUnit, const GLenum textureFormat);

    void bind();
};

