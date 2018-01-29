#include "Framebuffer.h"
#include "../RenderSettings.h"

FrameBufferObject::FrameBufferObject()
{
    init(g_renderSettings.resolutionX, g_renderSettings.resolutionY);
}

FrameBufferObject::FrameBufferObject(bool msaa, int resolutionX, int resolutionY)
{
    if(msaa) {
        if(resolutionX == 0 && resolutionY == 0) {
            initMSAA(g_renderSettings.resolutionX, g_renderSettings.resolutionY);
            width = g_renderSettings.resolutionX;
            height = g_renderSettings.resolutionY;
        } else {
            initMSAA(resolutionX, resolutionY);
            width = resolutionX;
            height = resolutionY;
        }
    } else {
        if(resolutionX == 0 && resolutionY == 0) {
            init(g_renderSettings.resolutionX, g_renderSettings.resolutionY);
            width = g_renderSettings.resolutionX;
            height = g_renderSettings.resolutionY;
        } else {
            init(resolutionX, resolutionY);
            width = resolutionX;
            height = resolutionY;
        }
    }
}

void FrameBufferObject::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, width, height);
}

GLuint FrameBufferObject::getColorTex()
{
    return m_colTex;
}

//MSAA ONLY
void FrameBufferObject::resolve(const FrameBufferObject& fbo)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.m_fbo);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glBlitFramebuffer(0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY, 0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY, GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void FrameBufferObject::init(int resolutionX, int resolutionY)
{
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    //Render texture
    glGenTextures(1, &m_colTex);
    glBindTexture(GL_TEXTURE_2D, m_colTex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, resolutionX, resolutionY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Bind render texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colTex, 0);

    glGenTextures(1, &m_depTex);
    glBindTexture(GL_TEXTURE_2D, m_depTex);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, resolutionX, resolutionY, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, NULL
    );


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depTex, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::initMSAA(int resolutionX, int resolutionY)
{
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glGenRenderbuffers(1, &m_colTex);
    glBindRenderbuffer(GL_RENDERBUFFER, m_colTex);

    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_RGBA32F, resolutionX, resolutionY);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colTex);

    glGenRenderbuffers(1, &m_depTex);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depTex);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_DEPTH_COMPONENT32,resolutionX, resolutionY);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depTex);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBufferObject::getDepthTex()
{
    return m_depTex;
}

void FrameBufferObject::clear()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}
