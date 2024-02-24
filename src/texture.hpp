#pragma once
#include "header.hpp"


class Texture {
    GLuint id;
public:
    Texture();
    Texture(std::string path);
    bool loadFromFile(std::string path);
    void use();
};