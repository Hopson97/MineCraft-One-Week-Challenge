#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

struct Config {
    int windowX = 1280;
    int windowY = 720;
    bool isFullscreen = false;
    int renderDistance = 8; // Set RD low to prevent long load times
    int fov = 90;
};

#endif // CONFIG_H_INCLUDED
