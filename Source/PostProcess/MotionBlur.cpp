#include "MotionBlur.h"

MotionBlur::MotionBlur()
    :   BasicShader("MBlur", "MBlur")
{
    getUniforms();
}

void MotionBlur::getUniforms()
{
    BasicShader::getUniforms();
    useProgram();
    t1 = glGetUniformLocation(m_id, "tex");
    t2 = glGetUniformLocation(m_id, "other");
    m_prev = glGetUniformLocation(m_id, "prevProjViewMatrix");
    m_curr = glGetUniformLocation(m_id, "currProjViewMatrix");
    m_res = glGetUniformLocation(m_id, "resolution");
}

void MotionBlur::loadT1()
{
    glUniform1i(t1, 0);
}

void MotionBlur::loadT2()
{
    glUniform1i(t2, 2);
}
void MotionBlur::loadPrevProj(glm::mat4 prev)
{
    loadMatrix4(m_prev, prev);
}
void MotionBlur::loadCurrProj(glm::mat4 curr)
{
    loadMatrix4(m_curr, curr);
}

void MotionBlur::loadRes(glm::vec2 v)
{
    loadVector2(m_res, v);
}
