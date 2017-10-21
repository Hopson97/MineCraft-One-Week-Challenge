#ifndef MASK2_H
#define MASK2_H

#include "../Shaders/BasicShader.h"

class Mask2Shader : public BasicShader{
public:
    Mask2Shader();
private:
    void getUniforms() override;
};

#endif