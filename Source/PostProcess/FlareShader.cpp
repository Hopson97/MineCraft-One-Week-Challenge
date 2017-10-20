#include "FlareShader.h"

FlareShader::FlareShader(): BasicShader("Flare", "Flare"){
    getUniforms();
}

void FlareShader::loadLocation(glm::vec2 loc){
    loadVector2(m_loc, loc);
}

void FlareShader::loadBrightness(float brightness){
    loadFloat(m_bright, brightness);
}

void FlareShader::getUniforms(){
    BasicShader::getUniforms();
    m_loc = glGetUniformLocation(m_id, "transform");
    m_bright = glGetUniformLocation(m_id, "brightness");
}
    