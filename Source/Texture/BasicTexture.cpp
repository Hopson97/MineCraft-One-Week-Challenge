#include "BasicTexture.h"
#include <iostream>
#include <cmath>
#include "../ShaderData.h"

BasicTexture::BasicTexture(const std::string& file)
{
    loadFromFile(file);
}

void BasicTexture::loadFromImage(const sf::Image& i)
{
    glGenTextures(1, &m_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr());

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //No mipmaps nearby
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
/**@TODO Add the extention `GLEW_EXT_texture_filter_anisotropic` to the GLAD gen file
    if(GLEW_EXT_texture_filter_anisotropic && g_ShaderSettings.aniso) {
        float max;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);
        float amount = std::min(16.0f, max);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, amount);
    }*/
}
void BasicTexture::loadFromFile(const std::string& file)
{
    sf::Image i;
    if(!i.loadFromFile("Res/Textures/" + file + ".png")) {
        throw std::runtime_error("Unable to load BasicTexture: " + file);
    }

    loadFromImage(i);
}

BasicTexture::~BasicTexture()
{
    glDeleteTextures(1, &m_id);
}

void BasicTexture::bindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}


GLuint BasicTexture::getID() const
{
    return m_id;
}
