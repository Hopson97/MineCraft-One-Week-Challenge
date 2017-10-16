#include "BasicFilter.h"

BaseFilter::BaseFilter(int framebufferX, int framebufferY){
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    //Render texture
    glGenTextures(1, &m_colTex);
    glBindTexture(GL_TEXTURE_2D, m_colTex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, framebufferX, framebufferY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Bind render texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colTex, 0);

    glGenTextures(1, &m_depTex);
    glBindTexture(GL_TEXTURE_2D, m_depTex);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32  , framebufferX, framebufferX, 0, 
        GL_DEPTH_COMPONENT, GL_FLOAT, NULL
      ); 
      
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depTex, 0);  
    
    //Disable new framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

GLuint BaseFilter::getOutputTexture(){
    return m_colTex;
}
GLuint BaseFilter::getDepthTexture(){
    return m_depTex;
}

void BaseFilter::add(const glm::vec3& position){
    m_quads.push_back(position);
}