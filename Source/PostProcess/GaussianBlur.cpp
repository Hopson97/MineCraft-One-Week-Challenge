#include "GaussianBlur.h"
#include "../RenderSettings.h"

GaussianBlur::GaussianBlur(): renderer((int)g_renderSettings.resolutionX,(int)g_renderSettings.resolutionY){
    
}

void GaussianBlur::render(GLuint texture){
    
    
    gh_shader.useProgram();
    gh_shader.loadTarget((float)g_renderSettings.resolutionX);
    gh_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gh_shader.loadModelMatrix(glm::mat4());
    //Bind shader
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    renderer.render();

    gh_shader.useProgram();
    gh_shader.loadTarget((float)g_renderSettings.resolutionX);
    gh_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gh_shader.loadModelMatrix(glm::mat4());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderer.getOutputTexture());
    renderer.render();

}