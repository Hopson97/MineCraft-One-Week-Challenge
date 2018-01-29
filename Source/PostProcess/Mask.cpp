#include "Mask.h"

MaskShader::MaskShader()
    :   BasicShader("Mask", "Mask")
{
    getUniforms();
}

void MaskShader::getUniforms()
{
    BasicShader::getUniforms();
    m_luma = glGetUniformLocation(m_id, "requestedLuminance");
}

void MaskShader::loadLuma(float luma)
{
    loadFloat(m_luma, luma);
}
