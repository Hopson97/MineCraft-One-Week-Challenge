#ifndef MASK_SHADER_H
#define MASK_SHADER_H

#include "../Shaders/BasicShader.h"

class MaskShader : public BasicShader{
public:
    MaskShader();
private:
    void getUniforms() override;
};

#endif