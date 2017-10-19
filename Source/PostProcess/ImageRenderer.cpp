#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(int width, int height){
    fbo = FrameBufferObject(width, height);
}

void ImageRenderer::render(GLuint texture){
    fbo.bind();
    fbo.clear();

    GL::drawElements(4);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //Unbind
}