#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#include "HorizontalGaussian.h"
#include "VerticalGaussian.h"
#include "ImageRenderer.h"

class GaussianBlur{
public:
    GaussianBlur();

    void render(GLuint texture);
    ImageRenderer renderer;
private:

    GaussianH gh_shader;
    GaussianV gv_shader;
};

#endif