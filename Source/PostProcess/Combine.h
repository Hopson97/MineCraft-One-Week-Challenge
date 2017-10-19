#ifndef COMBINE_H
#define COMBINE_H

#include "../Shaders/BasicShader.h"

class CombineShader : public BasicShader{
public:
    CombineShader();
private:
    void getUniforms() override;
};

#endif