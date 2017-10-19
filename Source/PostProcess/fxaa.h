#ifndef FXAA_H
#define FXAA_H

#include "../Shaders/BasicShader.h"

class FXAAShader : public BasicShader{
public:
    FXAAShader();
    void loadRes(glm::vec2 res);
private:
    void getUniforms() override;
    GLuint m_res;
};

#endif