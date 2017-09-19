#include "SunShader.h"

SunShader::SunShader()
:   BasicShader ("SunShaderVertex", "SunShaderFragment")
{
    getUniforms();
}

void SunShader::getUniforms(){
    BasicShader::getUniforms();
}