#ifndef G_V_SHADER_H
#define G_V_SHADER_H

#include "../Shaders/BasicShader.h"

class GaussianV : public BasicShader{
public:
    GaussianV();
    void loadTarget(float target);
private:
    void getUniforms() override;
    GLuint target;
};

#endif