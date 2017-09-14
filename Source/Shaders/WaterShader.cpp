#include "WaterShader.h"

WaterShader::WaterShader()
:   BasicShader ("WaterVertex", "WaterFragment")
{
    getUniforms();
}

void WaterShader::loadBrightness (const float& brightness){
    loadFloat(m_brightness, brightness);
}
void WaterShader::loadContrast (const float& contrast){
    loadFloat(m_contrast, contrast);
}
void WaterShader::loadGamma (const float& gamma){
    loadFloat(m_gamma, gamma);
}

void WaterShader::loadTime (const float& time){
    loadFloat(m_time, time);
}

void WaterShader::getUniforms()
{
    BasicShader::getUniforms();
    m_brightness = glGetUniformLocation(m_id, "brightness");
    m_contrast = glGetUniformLocation(m_id, "contrast");
    m_gamma = glGetUniformLocation(m_id, "gamma");
    m_time = glGetUniformLocation(m_id, "globalTime");
}

