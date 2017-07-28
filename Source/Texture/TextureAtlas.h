#ifndef TEXTUREATLAS_H_INCLUDED
#define TEXTUREATLAS_H_INCLUDED

#include "BasicTexture.h"

class TextureAtlas : public BasicTexture
{
    public:
        TextureAtlas(const std::string& textureFileName);

        std::vector<GLfloat> getTexture;

    private:
};

#endif // TEXTUREATLAS_H_INCLUDED
