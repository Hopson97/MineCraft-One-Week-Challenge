#ifndef IMAGE_RENDERER_H
#define IMAGE_RENDERER_H

#include "../GL/GLFunctions.h"
#include "Framebuffer.h"
//A lil based off thinmatrix

class ImageRenderer{
    ImageRenderer(int width, int height);
    void render(GLuint texture);

    inline GLuint getOutputTexture(){
        return fbo.getColorTex();
    }
private:
    FrameBufferObject fbo;
};

#endif