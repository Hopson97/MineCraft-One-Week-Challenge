#include "ImageRenderer.h"
#include <iostream>
ImageRenderer::ImageRenderer(int width, int height)
    :   fbo(false, width, height)
{ }

void ImageRenderer::render()
{
    fbo.bind();
    fbo.clear();

    GL::drawElements(6);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //Unbind
}
