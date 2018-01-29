#include "HorizontalGaussian.h"

GaussianH::GaussianH()
    :   BasicShader("GaussianH", "Gaussian")
{
    getUniforms();
}

void GaussianH::getUniforms()
{
    BasicShader::getUniforms();
    target = glGetUniformLocation(m_id, "target");
}

void GaussianH::loadTarget(float atarget)
{
    loadFloat(target, atarget);
}
