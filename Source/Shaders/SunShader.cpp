#include "SunShader.h"

SunShader::SunShader()
:   BasicShader ("Sun", "Sun")
{
    getUniforms();
}

void SunShader::loadTime(float tick){
    loadFloat(m_day, tick);
}

void SunShader::getUniforms(){
    BasicShader::getUniforms();
    m_day = glGetUniformLocation(m_id, "dayTime");
}