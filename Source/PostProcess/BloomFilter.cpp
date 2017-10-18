#include "BloomFilter.h"
#include "../RenderSettings.h"

BloomFilter::BloomFilter():fbo(false, g_renderSettings.resolutionX/2, g_renderSettings.resolutionY/2){
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

void BloomFilter::add(const glm::vec3& position){
    m_quads.push_back(position);
}

void BloomFilter::render(const Camera& camera, GLuint colTex)
{
    add(glm::vec3(-1, -1, -1));
    fbo.bind();
    //fbo.clear();
    
    glEnable(GL_TEXTURE_2D);

    if (m_quads.empty())
    {
        return;
    }
    

    //Set to texture

    /*//Mask
    mask_shader.useProgram();
    m_quadModel.bindVAO();
    mask_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    mask_shader.loadModelMatrix(glm::mat4());
    

    GL::drawElements(m_quadModel.getIndicesCount());
    */
    //Horizontal
    gh_shader.useProgram();
    m_quadModel.bindVAO();
    gh_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gh_shader.loadModelMatrix(glm::mat4());
    gh_shader.loadTarget(fbo.width);
    glBindTexture(GL_TEXTURE_2D, colTex);

    GL::drawElements(m_quadModel.getIndicesCount());
    
    //Vertical
    gv_shader.useProgram();
    m_quadModel.bindVAO();
    gv_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));
    gv_shader.loadModelMatrix(glm::mat4());
    gv_shader.loadTarget(fbo.height);
    glBindTexture(GL_TEXTURE_2D, fbo.getColorTex());

    GL::drawElements(m_quadModel.getIndicesCount());

    //Combine
    

    fbo.clear();
    
    //At the end
    m_quads.clear();
}
