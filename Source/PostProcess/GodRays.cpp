#include "GodRays.h"
#include "../RenderSettings.h"
#include "../GlobalInfo.h"

GodRays::GodRays()
    :   renderer(g_renderSettings.resolutionX, g_renderSettings.resolutionY)
{

}

void GodRays::render(GLuint texture)
{

    m_shader.useProgram();
    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    m_shader.loadModelMatrix(glm::mat4());
    m_shader.loadLuma(0.97f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    renderer.render();

    g_shader.useProgram();
    g_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    g_shader.loadModelMatrix(glm::mat4());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderer.getOutputTexture());
    renderer.render();


    c_shader.useProgram();
    c_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    c_shader.loadModelMatrix(glm::mat4());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    c_shader.loadTex(texture);

    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, renderer.getOutputTexture());
    c_shader.loadTex2(renderer.getOutputTexture());

    renderer.render();

    glActiveTexture(GL_TEXTURE0);
}
