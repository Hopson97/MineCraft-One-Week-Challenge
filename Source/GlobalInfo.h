#ifndef GLOBAL_INFO_H
#define GLOBAL_INFO_H

struct GlobalInfo{
    float lighting;
    int tickTime;
    int dayTime;
    float elapsedTime;
    float deltaTime;
};

extern GlobalInfo g_info;

#endif