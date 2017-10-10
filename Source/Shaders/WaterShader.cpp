#include "WaterShader.h"

WaterShader::WaterShader()
:   BasicShader ("Water", "Water")
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
    lighting = glGetUniformLocation(m_id, "lighting");
}

void WaterShader::loadLighting(float light){
    loadFloat(lighting, light);
} 
