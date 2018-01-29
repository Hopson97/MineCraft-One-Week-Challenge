#include "RenderMaster.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Chunk/ChunkSection.h"
#include "../Application.h"
#include "../Context.h"
#include "../Config.h"
#include "../RenderSettings.h"
#include "../PostProcess/Framebuffer.h"
#include "../ShaderData.h"



RenderMaster::RenderMaster(): fbo(false)
{

}

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
    m_sfmlRenderer.add(drawable);
}

void RenderMaster::drawChunk(const ChunkSection& chunk)
{
    //Since this pertains to here...
    if(g_Config.gamma > 2.0f) {
        g_Config.gamma = 1.3f;
    }
    if(g_Config.brightness > 1.5f) {
        g_Config.brightness = 1.15f;
    }
    if(g_Config.contrast > 2.5f) {
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


    fbo.bind();
    fbo.clear();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_chunkRenderer .render (camera, &g_Config);
    m_waterRenderer .render (camera, &g_Config);
    m_floraRenderer .render (camera, &g_Config);


    m_sky->render(camera);
    m_postRenderer.render(camera, fbo);

    m_sfmlRenderer  .render (window);

    window.display();
}
