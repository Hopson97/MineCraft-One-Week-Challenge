#include "Combine.h"

CombineShader::CombineShader():BasicShader("Combine", "Combine"){
    getUniforms();
}

void CombineShader::getUniforms(){
    BasicShader::getUniforms();

    GLuint t1 = glGetUniformLocation(m_id, "tex");
    GLuint t2 = glGetUniformLocation(m_id, "other");
    useProgram();
    glUniform1i(t1, 0);
    glUniform1i(t2, 1);
}