#ifndef POSTPROCESSSHADER_H_INCLUDED
#define POSTPROCESSSHADER_H_INCLUDED

#include "BasicShader.h"

class PostProcessShader : public BasicShader
{
    public:
        PostProcessShader();
    private:
        void getUniforms() override;
};

#endif // CHUNKSHADER_H_INCLUDED
