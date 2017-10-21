#ifndef RADIAL_H
#define RADIAL_H

#include "../Shaders/BasicShader.h"

class RadialShader : public BasicShader{
public:
    RadialShader();

    void loadResolution(glm::vec2 res);
    
private:
    void getUniforms() override;
    GLuint m_res;
};

#endif