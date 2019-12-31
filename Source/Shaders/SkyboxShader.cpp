#include "SkyboxShader.h"

SkyboxShader::SkyboxShader()
    : Shader("Skybox", "Skybox")
{
    getUniforms();
}

void SkyboxShader::loadViewMatrix(glm::mat4 viewMatrix)
{
    viewMatrix[3][0] = 0;
    viewMatrix[3][1] = 0;
    viewMatrix[3][2] = 0;
    Shader::loadMatrix4(m_locationView, viewMatrix);
}

void SkyboxShader::loadProjectionMatrix(const glm::mat4 &proj)
{
    Shader::loadMatrix4(m_locationProjection, proj);
}

void SkyboxShader::getUniforms()
{
    m_locationProjection = glGetUniformLocation(m_id, "projectionMatrix");
    m_locationView = glGetUniformLocation(m_id, "viewMatrix");
}
