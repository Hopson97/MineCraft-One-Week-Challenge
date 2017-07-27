#include "BasicShader.h"

BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile)
:   Shader(vertexFile, fragmentFile)
{

}

void BasicShader::loadProjectionViewMatrix(const glm::mat4& pvMatrix)
{
    loadMatrix4(m_locationProjectionViewMatrix,
                pvMatrix);
}

void BasicShader::getUniforms()
{
    m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMat");
}
