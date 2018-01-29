#include "FloraShader.h"
#include "../GlobalInfo.h"

FloraShader::FloraShader()
    :   BasicShader ("Flora", "Flora")
{
    getUniforms();
}


void FloraShader::loadTime (const float& time)
{
    loadFloat(m_time, time);
}

void FloraShader::loadLight(float lighting)
{
    loadFloat(m_light, lighting);
}

void FloraShader::loadDTime(float time)
{
    loadFloat(dtime, time);
}

void FloraShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
    m_light = glGetUniformLocation(m_id, "lighting");
    dtime = glGetUniformLocation(m_id, "dayTime");
}

