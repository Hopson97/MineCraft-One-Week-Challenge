#ifndef RENDER_SETTINGS_H
#define RENDER_SETTINGS_H

#include <GL/glew.h>

struct RenderSettings{
    int resolutionX;
    int resolutionY;
    GLuint fbo;
    GLuint colorTex;
    GLuint depthTex;

    //MSAA
    GLuint fboMSAA;
    GLuint rbo;
    GLuint colorBuffer;
    GLuint depthBuffer;
};
extern RenderSettings g_renderSettings;

#endif