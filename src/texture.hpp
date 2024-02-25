#pragma once
#include "header.hpp"


class Texture {
    GLuint _id;
    std::string _filePath;
    GLubyte* _localBuffer;
    int _width, _height, _bitsPerPixel;
    GLenum _target;
public:
    Texture();
    Texture(std::string path);
    ~Texture();
    bool loadFromFile(std::string path);
    void bind(uint slot = 0);
    void unbind();
};