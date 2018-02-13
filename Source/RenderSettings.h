#ifndef RENDER_SETTINGS_H
#define RENDER_SETTINGS_H

#include "GLAD/glad.h"

struct RenderSettings{
    int resolutionX;
    int resolutionY;
};
extern RenderSettings g_renderSettings;

#endif
