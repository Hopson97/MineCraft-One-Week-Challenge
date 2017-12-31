#ifndef GOD_RAYS_H
#define GOD_RAYS_H

#include "Mask.h"
#include "Combine.h"
#include "ImageRenderer.h"
#include "../RenderSettings.h"
#include "GodRayShader.h"

class GodRays{
public:
    GodRays();

    void render(GLuint texture);
    ImageRenderer renderer;

private:
    MaskShader m_shader;
    CombineShader c_shader;
    GodRayShader g_shader;
};


#endif