#include "Bloom.h"

Bloom::Bloom():renderer(g_renderSettings.resolutionX,g_renderSettings.resolutionY)
{

}

void Bloom::render(GLuint texture)
{

    m_shader.useProgram();
    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    m_shader.loadModelMatrix(glm::mat4());
    m_shader.loadLuma(0.83f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    renderer.render();

    gblur.render(renderer.getOutputTexture());

    c_shader.useProgram();
    c_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    c_shader.loadModelMatrix(glm::mat4());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    c_shader.loadTex(texture);

    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, gblur.renderer.getOutputTexture());
    c_shader.loadTex2(gblur.renderer.getOutputTexture());

    renderer.render();

    glActiveTexture(GL_TEXTURE0);
}
