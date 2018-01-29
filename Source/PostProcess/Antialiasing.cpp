#include "Antialiasing.h"

Antialiasing::Antialiasing():renderer(g_renderSettings.resolutionX,g_renderSettings.resolutionY)
{

}

void Antialiasing::render(GLuint texture)
{

    fxaa.useProgram();
    fxaa.loadRes(glm::vec2(g_renderSettings.resolutionX,g_renderSettings.resolutionY));
    fxaa.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    fxaa.loadModelMatrix(glm::mat4());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    renderer.render();
}
