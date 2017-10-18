#ifndef GV_SHADER_H
#define GV_SHADER_H

#include "../Shaders/BasicShader.h"

class GVShader : public BasicShader{
public:
    GVShader();

    void loadTarget(float target);
private:
    void getUniforms() override;
    GLuint m_target;
};

#endif