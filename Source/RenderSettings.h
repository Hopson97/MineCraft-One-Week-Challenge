#ifndef RENDER_SETTINGS_H
#define RENDER_SETTINGS_H

#include <GL/glew.h>

struct RenderSettings{
    int resolutionX;
    int resolutionY;
};
extern RenderSettings g_renderSettings;

#endif