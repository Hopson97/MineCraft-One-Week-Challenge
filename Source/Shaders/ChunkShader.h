#ifndef CHUNKSHADER_H_INCLUDED
#define CHUNKSHADER_H_INCLUDED

#include "BasicShader.h"

class ChunkShader : public BasicShader
{
    public:
        ChunkShader();

        void loadBrightness (const float& brightness);
        void loadContrast (const float& contrast);
        void loadGamma (const float& gamma);
    private:
        void getUniforms() override;

        GLuint m_brightness;
        GLuint m_contrast;
        GLuint m_gamma;
};

#endif // CHUNKSHADER_H_INCLUDED
