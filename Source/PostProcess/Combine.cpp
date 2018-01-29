#include "Combine.h"

CombineShader::CombineShader():BasicShader("Combine", "Combine")
{
    getUniforms();
}

void CombineShader::getUniforms()
{
    BasicShader::getUniforms();
    useProgram();
    t1 = glGetUniformLocation(m_id, "tex");
    t2 = glGetUniformLocation(m_id, "other");
}

void CombineShader::loadTex(GLuint tt1)
{
    glUniform1i(t1, 0);
}

void CombineShader::loadTex2(GLuint tt2)
{
    glUniform1i(t2, 2);
}
