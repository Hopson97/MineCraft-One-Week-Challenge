#ifndef RENDER_SETTINGS_H

#include <GL/glew.h>

struct RenderSettings{
    int resolutionX;
    int resolutionY;
    GLuint fbo;
    GLuint colorBuffer;
    GLuint depthBuffer;
    GLuint colorTex;
    GLuint depthTex;
};
extern RenderSettings g_renderSettings;

#endif