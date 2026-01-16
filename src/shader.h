#pragma once

#include <glad/glad.h>

#include <string>
#include <filesystem>

class Shader {
public:
    unsigned int ID;
    Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath);

    void use();

    void setBool(const std::string_view name, bool value) const;
    void setInt(const std::string_view name, int value) const;
    void setFloat(const std::string_view name, float value) const;

private:
    void checkCompileErrors(unsigned int shader, const std::string_view type);
};
