#ifndef G_H_SHADER_H
#define G_H_SHADER_H

#include "../Shaders/BasicShader.h"

class GaussianH : public BasicShader{
public:
    GaussianH();
    void loadTarget(float target);
private:
    void getUniforms() override;
    GLuint target;
};

#endif