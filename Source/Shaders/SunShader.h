#ifndef SUN_SHADER_H
#define SUN_SHADER_H

#include "BasicShader.h"

class SunShader : public BasicShader{
public:
    SunShader();

private:
    void getUniforms() override;
};


#endif