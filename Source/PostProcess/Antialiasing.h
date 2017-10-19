#ifndef ANTIALIASING_H
#define ANTIALIASING_H

#include "ImageRenderer.h"
#include "fxaa.h"
#include "../RenderSettings.h"
class Antialiasing{
public:
    Antialiasing();

    void render(GLuint texture);
    ImageRenderer renderer;
    
private:
    FXAAShader fxaa;
};


#endif