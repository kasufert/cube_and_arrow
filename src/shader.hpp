#pragma once
#include "header.hpp"

class Shader {
public:
    GLuint id;

    // Read and build
    Shader(const char* vertPath, const char* fragPath);
    // Use the shader
    void use();

    template<typename T> bool set(const std::string& name, T value);
};

template<typename T>
inline bool Shader::set(const std::string& name, T value)
{
    GLuint loc = glGetUniformLocation(id, name.c_str());
    if (loc == -1)
    {
        fmt::print("Uniform type of {} not yet implemented.\n", name);
        return false;
    }
    return true;
}