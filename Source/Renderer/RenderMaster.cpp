#include "RenderMaster.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Chunk/ChunkSection.h"
#include "../Application.h"
#include "../Context.h"
#include "../Config.h"
#include "../RenderSettings.h"

RenderMaster::RenderMaster()
{
    if (!setupFrameBuffers())
    {
        throw std::runtime_error("FRAME BUFFER ERROR: NOT COMPLETE");
    }
}

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
    m_sfmlRenderer.add(drawable);
}

void RenderMaster::drawChunk(const ChunkSection& chunk)
{
    //Since this pertains to here...
    if(g_Config.gamma > 2.0f)
    {
        g_Config.gamma = 1.3f;
    }
    if(g_Config.brightness > 1.5f)
    {
        g_Config.brightness = 1.15f;
    }
    if(g_Config.contrast > 2.5f)
    {
        g_Config.contrast = 1.1f;
    }
    
    const auto& solidMesh = chunk.getMeshes().solidMesh;
    const auto& waterMesh = chunk.getMeshes().waterMesh;
    const auto& floraMesh = chunk.getMeshes().floraMesh;

    if (solidMesh.faces > 0)
        m_chunkRenderer.add(solidMesh);

    if (waterMesh.faces > 0)
        m_waterRenderer.add(waterMesh);

    if (floraMesh.faces > 0)
        m_floraRenderer.add(floraMesh);
}

void RenderMaster::drawSky()
{
    m_drawBox = true;
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


    glBindFramebuffer(GL_FRAMEBUFFER, g_renderSettings.fbo); //Render to texture
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_chunkRenderer .render (camera, &g_Config);
    m_waterRenderer .render (camera, &g_Config);
    m_floraRenderer .render (camera, &g_Config);

    
    m_sky->render(camera);

    m_postRenderer.render(camera);

    m_sfmlRenderer  .render (window);

    window.display();
}

bool RenderMaster::setupFrameBuffers()
{
    glGenFramebuffers(1, &g_renderSettings.fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, g_renderSettings.fbo);

    //Render texture
    glGenTextures(1, &g_renderSettings.colorTex);
    glBindTexture(GL_TEXTURE_2D, g_renderSettings.colorTex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_renderSettings.resolutionX, g_renderSettings.resolutionY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Bind render texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_renderSettings.colorTex, 0);

    glGenTextures(1, &g_renderSettings.depthTex);
    glBindTexture(GL_TEXTURE_2D, g_renderSettings.depthTex);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32  , g_renderSettings.resolutionX, g_renderSettings.resolutionY, 0, 
        GL_DEPTH_COMPONENT, GL_FLOAT, NULL
      );
      
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, g_renderSettings.depthTex, 0);  
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    //Disable new framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}
