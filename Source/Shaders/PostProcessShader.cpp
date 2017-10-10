#include "PostProcessShader.h"

PostProcessShader::PostProcessShader()
:   BasicShader ("PostProcess", "PostProcess")
{
    getUniforms();
}

void PostProcessShader::loadContrast(float c){
    loadFloat(m_c, c);
}

void PostProcessShader::loadGamma(float g){
    loadFloat(m_g, g);
}

void PostProcessShader::loadBrightness(float b){
    loadFloat(m_b, b);
}

void PostProcessShader::loadPostProcess(float p){
    loadFloat(m_p, p);
}

void PostProcessShader::loadResolution(glm::vec2 resolution){
    loadVector2(m_res, resolution);
}

void PostProcessShader::getUniforms()
{
    BasicShader::getUniforms();
    m_c = glGetUniformLocation(m_id, "contrast");
    m_b = glGetUniformLocation(m_id, "brightness");
    m_g = glGetUniformLocation(m_id, "gamma");
    m_p = glGetUniformLocation(m_id, "postProcess");
    m_res = glGetUniformLocation(m_id, "resolution");
}
