#include "FloraShader.h"

FloraShader::FloraShader()
    : BasicShader("Flora", "Chunk")
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
}

void FloraShader::loadTime(const float &time)
{
    loadFloat(m_time, time);
}