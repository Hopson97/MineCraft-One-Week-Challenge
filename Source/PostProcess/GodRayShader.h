#ifndef GOD_RAYS_SHADER_H
#define GOD_RAYS_SHADER_H

#include "../Shaders/BasicShader.h"

class GodRayShader : public BasicShader{
public:
    GodRayShader();
private:
    void getUniforms() override;
};

#endif