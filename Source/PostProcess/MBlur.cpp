#include "MBlur.h"

MBlur::MBlur()
:   renderer(g_renderSettings.resolutionX, g_renderSettings.resolutionY)
{
    prev = glm::mat4(1.0f);
}

void MBlur::render(const Camera& cam, FrameBufferObject& fbo)
{
    m_shader.useProgram();
    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    m_shader.loadModelMatrix(glm::mat4());
    m_shader.loadCurrProj(cam.getProjectionViewMatrix());
    m_shader.loadPrevProj(prev);
    m_shader.loadRes(glm::vec2(g_renderSettings.resolutionX, g_renderSettings.resolutionY));
    prev = cam.getProjectionViewMatrix();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo.getColorTex());

    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, fbo.getDepthTex());

    renderer.render();

    glActiveTexture(GL_TEXTURE0);
}
