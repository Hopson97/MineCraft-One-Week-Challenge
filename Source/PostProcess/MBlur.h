#ifndef M_BLUR_H
#define M_BLUR_H

#include "MotionBlur.h"
#include "../RenderSettings.h"
#include "ImageRenderer.h"
#include "Framebuffer.h"
#include "../Camera.h"

class Camera;

class MBlur{
public:
    MBlur();

    void render(const Camera& camera, FrameBufferObject& fbo);
    ImageRenderer renderer;
private:
    MotionBlur m_shader;
    glm::mat4 prev;
};

#endif