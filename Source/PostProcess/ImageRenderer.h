#ifndef IMAGE_RENDERER_H
#define IMAGE_RENDERER_H

#include "../GL/GLFunctions.h"
#include "Framebuffer.h"
//A lil based off thinmatrix

class ImageRenderer{
public:
    ImageRenderer(int width, int height);
    void render();

    GLuint getOutputTexture(){
        return fbo.getColorTex();
    }

    FrameBufferObject fbo;
private:
};

#endif