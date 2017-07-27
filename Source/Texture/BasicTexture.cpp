#include "BasicTexture.h"

#include <SFML/Graphics.hpp>

BasicTexture::BasicTexture(const std::string& file)
{
    loadFromFile(file);
}

void BasicTexture::loadFromFile(const std::string& file)
{
    sf::Image i;
    if(!i.loadFromFile("Res/Textures/" + file + ".png"))
    {
        ///@TODO Throw error
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

BasicTexture::~BasicTexture()
{
    glDeleteTextures(1, &m_id);
}

void BasicTexture::bindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}


