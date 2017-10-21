#include "Godrays.h"

Godrays::Godrays():renderer(g_renderSettings.resolutionX,g_renderSettings.resolutionY){

}

void Godrays::render(GLuint texture){

    m_shader.useProgram();
    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    m_shader.loadModelMatrix(glm::mat4());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    renderer.render();

    r_shader.useProgram();
    r_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    r_shader.loadModelMatrix(glm::mat4());
    r_shader.loadResolution(glm::vec2(g_renderSettings.resolutionX,g_renderSettings.resolutionY));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderer.getOutputTexture());
    renderer.render();
/*
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
    */
}