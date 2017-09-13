#include "ChunkShader.h"

ChunkShader::ChunkShader()
:   BasicShader ("ChunkVertex", "ChunkFragment")
{
    getUniforms();
}

void ChunkShader::loadBrightness (const float& brightness){
    loadFloat(m_brightness, brightness);
}
void ChunkShader::loadContrast (const float& contrast){
    loadFloat(m_contrast, contrast);
}
void ChunkShader::loadGamma (const float& gamma){
    loadFloat(m_gamma, gamma);
}

void ChunkShader::getUniforms()
{
    BasicShader::getUniforms();
    m_brightness = glGetUniformLocation(m_id, "brightness");
    m_contrast = glGetUniformLocation(m_id, "contrast");
    m_gamma = glGetUniformLocation(m_id, "gamma");
}
