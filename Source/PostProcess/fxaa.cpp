#include "fxaa.h"

FXAAShader::FXAAShader()
:   BasicShader("fxaa","fxaa")
{
    getUniforms();
}

void FXAAShader::getUniforms()
{
    BasicShader::getUniforms();
    m_res = glGetUniformLocation(m_id, "resolution");
}

void FXAAShader::loadRes(glm::vec2 v)
{
    loadVector2(m_res, v);
}
