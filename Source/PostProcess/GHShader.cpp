#include "GHShader.h"

GHShader::GHShader():BasicShader("GaussianH", "GaussianH"){
    getUniforms();
}

void GHShader::getUniforms(){
    BasicShader::getUniforms ();
    m_target = glGetUniformLocation(m_id, "target");
}


void GHShader::loadTarget(float target){
    loadFloat(m_target, target);
}