#ifndef GLOBAL_INFO_H
#define GLOBAL_INFO_H

#include "Camera.h"

class Camera;

struct GlobalInfo{
    float lighting;
    int tickTime;
    int dayTime;
    float elapsedTime;
    float deltaTime;
    Camera* cam;
};

extern GlobalInfo g_info;

#endif