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

    //Clear Screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //Set to screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY);
    
    //Set up the temp FBO
    pfbo.bind();
    pfbo.clear();

    //Get the input texture
    glBindTexture(GL_TEXTURE_2D, fbo.getColorTex()); //Set to texture
    
    //Gaussian H
    gh_shader.useProgram();
    gh_shader.loadTarget(pfbo.width);
    m_quadModel.bindVAO();
    gh_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gh_shader.loadModelMatrix(glm::mat4() );
    GL::drawElements(m_quadModel.getIndicesCount());

    glBindTexture(GL_TEXTURE_2D, pfbo.getColorTex());
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY);    

    //Gaussian V
    gv_shader.useProgram();
    gv_shader.loadTarget(pfbo.height);
    m_quadModel.bindVAO();
    gh_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gh_shader.loadModelMatrix(glm::mat4() );
    GL::drawElements(m_quadModel.getIndicesCount());

    glBindTexture(GL_TEXTURE_2D, pfbo.getColorTex());
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY);   

    fbo.bind();
    fbo.clear();
    glBindTexture(GL_TEXTURE_2D, pfbo.getColorTex());
    //Color re-balance of Post Process
    m_shader.useProgram();
    m_shader.loadGamma(g_Config.gamma);
    m_shader.loadContrast(g_Config.contrast);
    m_shader.loadBrightness(g_Config.brightness);
    m_shader.loadResolution(glm::vec2(g_Config.windowX, g_Config.windowY));
    
    m_quadModel.bindVAO();

    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));

    m_shader.loadModelMatrix(glm::mat4() );
    GL::drawElements(m_quadModel.getIndicesCount());
    

    //Final display
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo.m_fbo);
    glBlitFramebuffer(0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY, 0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY, GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT, GL_NEAREST);

    m_quads.clear();
}

