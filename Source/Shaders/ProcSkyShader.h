#ifndef PROC_SKY_SHADER_H
#define PROC_SKY_SHADER_H

#include "BasicShader.h"

class ProcSkyShader : BasicShader{
    ProcSkyShader();
    void loadTime(float ticks);
private:
    void getUniforms() override;
    GLuint m_day;
};

#endif