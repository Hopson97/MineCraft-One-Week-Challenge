#include "FloraShader.h"

FloraShader::FloraShader()
    : BasicShader("Flora", "Chunk")
{
    getUniforms();
}

void FloraShader::loadTime(const float &time)
{
    loadFloat(m_time, time);
}

void FloraShader::getUniforms()
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
}
