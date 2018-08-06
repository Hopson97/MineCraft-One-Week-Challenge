#include "PostProcessShader.h"

PostProcessShader::PostProcessShader()
:   BasicShader ("PostProcess", "PostProcess")
{
    getUniforms();
}

void PostProcessShader::getUniforms()
{
    BasicShader::getUniforms();
}
