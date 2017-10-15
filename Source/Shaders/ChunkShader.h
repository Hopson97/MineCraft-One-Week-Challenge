#ifndef CHUNKSHADER_H_INCLUDED
#define CHUNKSHADER_H_INCLUDED

#include "BasicShader.h"

class ChunkShader : public BasicShader
{
    public:
        ChunkShader();

        void loadLighting(float light);
        void loadDTime(float dayTime);
    private:
        void getUniforms() override;
        GLuint lighting;
        GLuint dtime;
};

#endif // CHUNKSHADER_H_INCLUDED
