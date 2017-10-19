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

void PostProcessRender::render(const Camera& camera, FrameBufferObject& fbo)
{
    begin();

    bloom.render(fbo.getColorTex());

    glBindTexture(GL_TEXTURE_2D, bloom.renderer.getOutputTexture()); //Bind final image
    finalize();
    end();
}

void PostProcessRender::begin(){
    //Clear Screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //Set to screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY);

    //Prepare for rendering
    glDisable(GL_DEPTH_TEST);
    m_quadModel.bindVAO(); //Stays bound
}

void PostProcessRender::end(){
    glEnable(GL_DEPTH_TEST);
}

void PostProcessRender::finalize(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0); //Set to screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, g_renderSettings.resolutionX, g_renderSettings.resolutionY);
    m_shader.useProgram();
    m_shader.loadGamma(g_Config.gamma);
    m_shader.loadContrast(g_Config.contrast);
    m_shader.loadBrightness(g_Config.brightness);
    m_shader.loadResolution(glm::vec2(g_Config.windowX, g_Config.windowY));
    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    m_shader.loadModelMatrix(glm::mat4());
    GL::drawElements(m_quadModel.getIndicesCount());
}