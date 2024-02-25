#include "texture.hpp"



Texture::Texture()
    : _id(UINT_MAX), _filePath(std::string()), _localBuffer(NULL), _width(0), _height(0), _bitsPerPixel(0), _target(GL_TEXTURE_2D)
{
}

Texture::Texture(std::string path)
    : Texture()
{
    _filePath = path;
    loadFromFile(_filePath);
}

Texture::~Texture()
{
}

bool Texture::loadFromFile(std::string path)
{
    sf::Image img;
    if (!img.loadFromFile(path))
    {
        fmt::print("Couldn't load file {}\n", path);
        return false;
    }
    img.flipVertically();
    _width = img.getSize().x;
    _height = img.getSize().y;
    _bitsPerPixel = 32;


    GLCALL(glGenTextures(1, &_id));
    GLCALL(glBindTexture(_target, _id));
    GLCALL(glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_CLAMP));
    GLCALL(glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_CLAMP));

    GLCALL(glTexImage2D(_target, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr()));

    unbind();

    return true;
}

void Texture::bind(uint slot)
{
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(_target, _id));
}

void Texture::unbind()
{
    GLCALL(glBindTexture(_target, 0));
}
