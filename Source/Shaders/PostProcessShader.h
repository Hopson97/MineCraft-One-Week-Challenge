#ifndef POSTPROCESSSHADER_H_INCLUDED
#define POSTPROCESSSHADER_H_INCLUDED

#include "BasicShader.h"

class PostProcessShader : public BasicShader
{
    public:
        PostProcessShader();
        
        void loadContrast(float c);
        void loadGamma(float g);
        void loadBrightness(float b);
        void loadPostProcess(float p);
        void loadResolution(glm::vec2 resolution);

    private:
        void getUniforms() override;

        GLuint m_c;
        GLuint m_b;
        GLuint m_g;
        GLuint m_p;
        GLuint m_res;
};

#endif // CHUNKSHADER_H_INCLUDED
