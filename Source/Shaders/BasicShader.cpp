#include "BasicShader.h"

/// @brief Basic Shader initializing GLSL files.
BasicShader::BasicShader(const std::string &vertexFile,
                         const std::string &fragmentFile)
    : Shader(vertexFile, fragmentFile)
{
    getUniforms();
}

void BasicShader::loadProjectionViewMatrix(const glm::mat4 &pvMatrix)
{
    loadMatrix4(m_locationProjectionViewMatrix, pvMatrix);
}

void BasicShader::loadModelMatrix(const glm::mat4 &matrix)
{
    loadMatrix4(m_locationModelMatrix, matrix);
}

/// @brief Once the shader is established, the uniforms are set.
void BasicShader::getUniforms()
{
    useProgram();
    m_locationProjectionViewMatrix =
        glGetUniformLocation(m_id, "projViewMatrix");
    m_locationModelMatrix = glGetUniformLocation(m_id, "modelMatrix");
}
