#ifndef GODRAYS_H
#define GODRAYS_H

#include "Mask2.h"
#include "Combine.h"
#include "ImageRenderer.h"
#include "../RenderSettings.h"
#include "Radial.h"

class Godrays{
public:
    Godrays();

    void render(GLuint texture);
    ImageRenderer renderer;

private:
    Mask2Shader m_shader;
    CombineShader c_shader;
    RadialShader r_shader;
};

#endif