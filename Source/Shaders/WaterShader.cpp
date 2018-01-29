#include "WaterShader.h"
#include "../GlobalInfo.h"

WaterShader::WaterShader()
    :   BasicShader ("Water", "Water")
{
    getUniforms();
}


void WaterShader::loadTime (const float& time)
{
    loadFloat(m_time, time);
}

void WaterShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
    lighting = glGetUniformLocation(m_id, "lighting");
    dtime= glGetUniformLocation(m_id, "dayTime");
}

void WaterShader::loadLighting(float light)
{
    loadFloat(lighting, light);
}

void WaterShader::loadDTime(float time)
{
    loadFloat(dtime, g_info.dayTime);
}
