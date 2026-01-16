#pragma once

#include <glad/glad.h>

#include <string>
#include <filesystem>

class Shader {
public:
    unsigned int ID;
    Shader(const std::filesystem::path vertexPath, const std::filesystem::path fragmentPath);

    void use();

    void setBool(const std::string_view name, const bool value) const;
    void setInt(const std::string_view name, const int value) const;
    void setFloat(const std::string_view name, const float value) const;

private:
    void checkCompileErrors(const unsigned int shader, const std::string_view type);
};
