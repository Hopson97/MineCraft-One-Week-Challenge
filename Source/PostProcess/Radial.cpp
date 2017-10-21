#include "Radial.h"

RadialShader::RadialShader(): BasicShader("WhiteMask", "WhiteMask"){
    getUniforms();
}

void RadialShader::getUniforms(){
    BasicShader::getUniforms();
    m_res = glGetUniformLocation(m_id, "resolution");
}

void RadialShader::loadResolution(glm::vec2 res){
    loadVector2(m_res, res);
}