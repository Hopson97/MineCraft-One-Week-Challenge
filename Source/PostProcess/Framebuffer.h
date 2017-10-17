#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

class FrameBufferObject{
public:
    FrameBufferObject();
    FrameBufferObject(bool msaa, int resolutionX=0, int resolutionY=0);

    void bind();
    GLuint getColorTex();
    
    //Only available with MSAA
    void resolve(const FrameBufferObject& fbo);


    GLuint m_fbo;
private:
    void init(int resolutionX, int resolutionY);
    void initMSAA(int resolutionX, int resolutionY);

    GLuint m_colTex;
    GLuint m_depTex;
};

#endif