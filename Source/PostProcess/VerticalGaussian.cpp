#include "VerticalGaussian.h"

GaussianV::GaussianV()
    :   BasicShader("GaussianV", "Gaussian")
{
    getUniforms();
}

void GaussianV::getUniforms()
{
    BasicShader::getUniforms();
    target = glGetUniformLocation(m_id, "target");
}

void GaussianV::loadTarget(float atarget)
{
    loadFloat(target, atarget);
}
