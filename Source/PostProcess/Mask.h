#ifndef MASK_H
#define MASK_H

#include "../Shaders/BasicShader.h"

class MaskShader : public BasicShader{
public:
    MaskShader();
private:
    void getUniforms() override;
};

#endif