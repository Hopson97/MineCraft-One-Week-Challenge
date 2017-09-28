#include "WaterShader.h"

WaterShader::WaterShader()
:   BasicShader ("WaterVertex", "WaterFragment")
{
    getUniforms();
}


void WaterShader::loadTime (const float& time){
    loadFloat(m_time, time);
}

void WaterShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
}

