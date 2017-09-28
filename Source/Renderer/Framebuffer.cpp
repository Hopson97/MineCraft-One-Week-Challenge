#include "Framebuffer.h"
#include <iostream>

GLuint g_FBO;
GLuint g_Tex;
GLuint g_RBO;

bool setupFrameBuffers(){

    glGenFramebuffers(1, &g_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, g_FBO);

    //Render texture
    glGenTextures(1, &g_Tex);
    glBindTexture(GL_TEXTURE_2D, g_Tex);
      
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_X, g_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  

    //Bind render texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_Tex, 0);    

    //Render Buffer
    glGenRenderbuffers(1, &g_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, g_RBO); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, g_X, g_Y);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //Bind render buffer to framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, g_RBO);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  
        std::cout << "FRAME BUFFER ERROR: NOT COMPLETE" << std::endl;
        return false;
    }

    //Disable new framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   

    return true;
}