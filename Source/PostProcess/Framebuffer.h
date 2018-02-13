#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../GLAD/glad.h"

class FrameBufferObject{
public:
    FrameBufferObject();
    FrameBufferObject(bool msaa, int resolutionX=0, int resolutionY=0);

    void bind();
    void clear(); //I didn't figure this out for 2 days........
    GLuint getColorTex();
    GLuint getDepthTex();

    //Only available with MSAA
    void resolve(const FrameBufferObject& fbo);


    GLuint m_fbo;
    int width, height;
private:
    void init(int resolutionX, int resolutionY);
    void initMSAA(int resolutionX, int resolutionY);

    GLuint m_colTex;
    GLuint m_depTex;
};

#endif
