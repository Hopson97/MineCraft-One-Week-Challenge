#include "TextureAtlas.h"
#include <array>

TextureAtlas::TextureAtlas(const std::string &textureFileName)
{
    sf::Image i;
    if (!i.loadFromFile("Res/Textures/" + textureFileName + ".png")) {
        throw std::runtime_error("Unable to open image: " + textureFileName);
    }
    loadFromImage(i);

    m_imageSize = 256;
    m_individualTextureSize = 16;
}

std::array<GLfloat, 8> TextureAtlas::getTexture(const sf::Vector2i &coords)
{
    static const GLfloat TEX_PER_ROW =
        (GLfloat)m_imageSize / (GLfloat)m_individualTextureSize;
    static const GLfloat INDV_TEX_SIZE = 1.0f / TEX_PER_ROW;
    static const GLfloat PIXEL_SIZE = 1.0f / (float)m_imageSize;

    GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;
    GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;

    GLfloat xMax = (xMin + INDV_TEX_SIZE) - PIXEL_SIZE;
    GLfloat yMax = (yMin + INDV_TEX_SIZE) - PIXEL_SIZE;

    return {xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin};
}
