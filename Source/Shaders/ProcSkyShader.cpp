#include "ProcSkyShader.h"

ProcSkyShader::ProcSkyShader()
:   BasicShader ("ProcSky", "ProcSky")
{
    getUniforms();
}

void ProcSkyShader::loadTime(float tick){
    loadFloat(m_day, tick);
}

void ProcSkyShader::getUniforms(){
    BasicShader::getUniforms();
    m_day = glGetUniformLocation(m_id, "dayTime"); //Useful
}