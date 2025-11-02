#include "WaterShader.h"

WaterShader::WaterShader()
    : BasicShader("Water", "Chunk")
{
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "globalTime");
}

void WaterShader::loadTime(const float &time)
{
    loadFloat(m_time, time);
}
