#pragma once
#include "shader.hpp"

Shader::Shader(const char* vertPath, const char* fragPath)
{
    GLuint vertexShader = GLCALL(glCreateShader(GL_VERTEX_SHADER));
    std::string vertShaderSrcStr = ReadFile(vertPath);
    const char* vertShaderSrc = vertShaderSrcStr.c_str();
    GLCALL(glShaderSource(vertexShader, 1, &vertShaderSrc, NULL));
    GLCALL(glCompileShader(vertexShader));
    // Check for shader compilation errors
    GLint success = -1;
    char infoLog[512];
    GLCALL(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GLCALL(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
        fmt::print("Error::Shader::Vertex::Compilation_Failed: Message:\n{}\n", infoLog);
    }

    GLuint fragShader = GLCALL(glCreateShader(GL_FRAGMENT_SHADER));
    std::string fragSrc = ReadFile(fragPath);
    const char* fragSrcStr = fragSrc.c_str();
    GLCALL(glShaderSource(fragShader, 1, &fragSrcStr, NULL));
    GLCALL(glCompileShader(fragShader));
    // Check for shader compilation errors
    GLCALL(glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GLCALL(glGetShaderInfoLog(fragShader, 512, NULL, infoLog));
        fmt::print("Error::Shader::Fragment::Compilation_Failed: Message:\n{}\n", infoLog);
        __debugbreak();

    }

    GLuint shaderProgram = glCreateProgram();
    GLCALL(glAttachShader(shaderProgram, vertexShader));
    GLCALL(glAttachShader(shaderProgram, fragShader));
    GLCALL(glLinkProgram(shaderProgram));
    // Error check
    GLCALL(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
    if (!success)
    {
        GLCALL(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
        fmt::print("Shader Program failed to link: Message: \n{}\n", infoLog);
        __debugbreak();
    }
    id = shaderProgram;

    ASSERT(glIsShader(vertexShader));
    ASSERT(glIsShader(fragShader));
    ASSERT(glIsProgram(id))

    // Delete old and no longer needed shader objects
        GLCALL(glDetachShader(id, vertexShader));
    GLCALL(glDetachShader(id, fragShader));
    GLCALL(glDeleteShader(vertexShader));
    GLCALL(glDeleteShader(fragShader));

}

void Shader::use()
{
    GLCALL(glUseProgram(id));
}

template<>
bool Shader::set(const std::string& name, float value)
{
    GLuint loc = GLCALL(glGetUniformLocation(id, name.c_str()));
    if (loc == -1)
    {
        fmt::print("Uniform \"{}\" not found or is invalid.\n", name);
        return false;
    }
    use();
    GLCALL(glUniform1f(loc, value));
    return true;
}

template<>
bool Shader::set(const std::string& name, int value)
{
    GLuint loc = GLCALL(glGetUniformLocation(id, name.c_str()));
    if (loc == -1)
    {
        fmt::print("Uniform \"{}\" not found or is invalid.\n", name);
        return false;
    }
    use();
    GLCALL(glUniform1i(loc, value));
    return true;
}

template<>
bool Shader::set(const std::string& name, glm::vec2 value)
{
    GLuint loc = GLCALL(glGetUniformLocation(id, name.c_str()));
    if (loc == -1)
    {
        fmt::print("Uniform \"{}\" not found or is invalid.\n", name);
        return false;
    }
    use();
    GLCALL(glUniform2fv(loc, 1, &value[0]));
    return true;
}

template<>
bool Shader::set(const std::string& name, glm::vec3 value)
{
    GLuint loc = GLCALL(glGetUniformLocation(id, name.c_str()));
    if (loc == -1)
    {
        fmt::print("Uniform \"{}\" not found or is invalid.\n", name);
        return false;
    }
    use();
    GLCALL(glUniform3fv(loc, 1, &value[0]));
    return true;
}

template<>
bool Shader::set(const std::string& name, glm::vec4 value)
{
    GLuint loc = GLCALL(glGetUniformLocation(id, name.c_str()));
    if (loc == -1)
    {
        fmt::print("Uniform \"{}\" not found or is invalid.\n", name);
        return false;
    }
    use();
    GLCALL(glUniform4fv(loc, 1, &value[0]));
    return true;
}


template<>
bool Shader::set(const std::string& name, glm::mat4 value)
{
    GLuint loc = GLCALL(glGetUniformLocation(id, name.c_str()));
    if (loc == -1)
    {
        fmt::print("Uniform \"{}\" not found or is invalid.\n", name);
        return false;
    }
    use();
    GLCALL(glUniformMatrix4fv(loc, 1, GL_FALSE, &(value[0][0])));
    return true;
}