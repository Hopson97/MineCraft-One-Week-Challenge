#ifndef GH_SHADER_H
#define GH_SHADER_H

#include "../Shaders/BasicShader.h"

class GHShader : public BasicShader{
public:
    GHShader();

    void loadTarget(float target);
private:
    void getUniforms() override;
    GLuint m_target;
};

#endif