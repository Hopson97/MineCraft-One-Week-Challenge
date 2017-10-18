#include "PostProcessRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Maths/Matrix.h"
#include "../RenderSettings.h"

PostProcessRender::PostProcessRender()
{
    m_quadModel.addData({
    {
        -0,  1, 0,
         1,  1, 0,
         1, -0, 0,
        -0, -0, 0,
    },
    {
        0, 1,
        1, 1,
        1, 0,
        0, 0,
    },
    {
        0, 1, 2,
        2, 3, 0
    }});
}

void PostProcessRender::add(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void PostProcessRender::render(const Camera& camera, FrameBufferObject& fbo, FrameBufferObject& pfbo)
{
    add(glm::vec3(-1, -1, -1));
    if (m_quads.empty())
    {
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0); //Set to screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY);
    glBindTexture(GL_TEXTURE_2D, fbo.getColorTex()); //Set to texture
    fbo.bind();

    m_shader.loadGamma(g_Config.gamma);
    m_shader.loadContrast(g_Config.contrast);
    m_shader.loadBrightness(g_Config.brightness);
    m_shader.loadResolution(glm::vec2(g_Config.windowX, g_Config.windowY));
    
    m_quadModel.bindVAO();

    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));

    m_shader.loadModelMatrix(glm::mat4() );
    GL::drawElements(m_quadModel.getIndicesCount());
    

    //Blit framebuffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo.m_fbo);
    glBlitFramebuffer(0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY, 0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY, GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT, GL_NEAREST);

    m_quads.clear();
}

