#ifndef FLARE_SHADER_H
#define FLARE_SHADER_H

#include "../Shaders/BasicShader.h"

class FlareShader : public BasicShader{
public:
    FlareShader();

    void loadLocation(glm::vec2 loc);
    void loadBrightness(float brightness);
private:
    void getUniforms() override;
    GLuint m_loc;
    GLuint m_bright;
};

#endif