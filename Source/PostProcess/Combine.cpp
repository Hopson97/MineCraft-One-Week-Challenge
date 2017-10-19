#include "Combine.h"

CombineShader::CombineShader():BasicShader("Combine", "Combine"){
    getUniforms();
}

void CombineShader::getUniforms(){
    BasicShader::getUniforms();

    t1 = glGetUniformLocation(m_id, "tex");
    t2 = glGetUniformLocation(m_id, "other");
    useProgram();
}

void CombineShader::loadTex(GLuint tt1){
    loadInt(t1, tt1);
}

void CombineShader::loadTex2(GLuint tt2){
    loadInt(t2, tt2);
}