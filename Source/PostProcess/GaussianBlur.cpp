#include "GaussianBlur.h"
#include "../RenderSettings.h"

GaussianBlur::GaussianBlur(): renderer((int)g_renderSettings.resolutionX/2,(int)g_renderSettings.resolutionY/2), renderer2((int)g_renderSettings.resolutionX/2,(int)g_renderSettings.resolutionY/2){
    
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
    renderer2.render();

}