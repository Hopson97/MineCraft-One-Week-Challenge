#include "RenderMaster.h"

#include <SFML/Graphics.hpp>
#include "Framebuffer.h"
#include <iostream>

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Chunk/ChunkSection.h"
#include "../Application.h"
#include "../Context.h"


void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
    m_sfmlRenderer.add(drawable);
}

void RenderMaster::drawQuad(const glm::vec3& pos)
{
    m_quadRenderer.add(pos);
}

void RenderMaster::drawCube(const Entity& cube)
{
    m_cubeRenderer.add(cube);
}

void RenderMaster::drawChunk(const ChunkSection& chunk)
{
    const ChunkMesh& solidMesh = chunk.getMeshes().solidMesh;
    const ChunkMesh& waterMesh = chunk.getMeshes().waterMesh;

    if (solidMesh.faces > 0)
        m_chunkRenderer.add(solidMesh);

    if (waterMesh.faces > 0)
        m_waterRenderer.add(waterMesh);
}

void RenderMaster::drawSky()
{
    m_drawBox = true;
}

void RenderMaster::setConfig(const Config con){
    m_conf = con;
    if(m_conf.gamma > 2.0f){
        m_conf.gamma = 1.3f;
    }
    if(m_conf.brightness > 1.5f){
        m_conf.brightness = 1.15f;
    }
    if(m_conf.contrast > 2.5f){
        m_conf.contrast = 1.1f;
    }
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    

    glBindFramebuffer(GL_FRAMEBUFFER, g_FBO); //Render to texture
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //m_quadRenderer  .render (camera);
    //m_cubeRenderer  .render (camera);
    m_chunkRenderer .render (camera, &m_conf);
    m_waterRenderer .render (camera, &m_conf);

    if (m_drawBox)
    {
        glDisable(GL_CULL_FACE);
        m_skyboxRenderer.render (camera);
        m_drawBox = false;
    }
    

    glBindFramebuffer(GL_FRAMEBUFFER, 0); //Set to screen
    glViewport(0, 0, g_X, g_Y);
    glBindTexture(GL_TEXTURE_2D, g_Tex); //Set to texture

    m_quadRenderer.add(glm::vec3(-1, -1, -1));
    m_quadRenderer.render(camera, &m_conf);

    m_sfmlRenderer  .render (window);

    window.display();
}
