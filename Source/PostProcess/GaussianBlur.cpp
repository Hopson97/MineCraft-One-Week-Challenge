#include "GaussianBlur.h"
#include "../RenderSettings.h"

GaussianBlur::GaussianBlur()
:   renderer((int)g_renderSettings.resolutionX/2, (int)g_renderSettings.resolutionY/2)
{

}

void GaussianBlur::render(GLuint texture)
{
    gh_shader.useProgram();
    gh_shader.loadTarget((float)g_renderSettings.resolutionX/2);
    gh_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gh_shader.loadModelMatrix(glm::mat4());
    //Bind shader
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    renderer.render();

    gv_shader.useProgram();
    gv_shader.loadTarget((float)g_renderSettings.resolutionY/2);
    gv_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gv_shader.loadModelMatrix(glm::mat4());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderer.getOutputTexture());
    renderer.render();

}
