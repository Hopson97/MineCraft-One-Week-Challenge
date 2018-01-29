#include "ProcSkyShader.h"

ProcSkyShader::ProcSkyShader()
    :   BasicShader ("ProcSky", "ProcSky")
{
    getUniforms();
}

void ProcSkyShader::loadTime(float tick)
{
    loadFloat(m_day, tick);
}

void ProcSkyShader::loadViewMatrix(glm::mat4 viewMatrix)
{
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    Shader::loadMatrix4(m_locationView, viewMatrix);
}


void ProcSkyShader::loadProjectionMatrix(const glm::mat4& proj)
{
    Shader::loadMatrix4(m_locationProjection, proj);
}

void ProcSkyShader::getUniforms()
{
    BasicShader::getUniforms();
    m_day = glGetUniformLocation(m_id, "dayTime"); //Useful
    m_locationProjection    = glGetUniformLocation(m_id, "projectionMatrix");
    m_locationView = glGetUniformLocation(m_id, "viewMatrix");
}
