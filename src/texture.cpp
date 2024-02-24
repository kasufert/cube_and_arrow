#include "texture.hpp"



Texture::Texture()
{
    id = -1;
}

Texture::Texture(std::string path)
{
    id = -1;
    loadFromFile(path);
}

bool Texture::loadFromFile(std::string path)
{
    sf::Image img;
    img.loadFromFile(path);


    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

void Texture::use()
{
    glBindTexture(GL_TEXTURE_2D, id);
}
