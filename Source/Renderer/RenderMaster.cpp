#include "RenderMaster.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Application.h"
#include "../Context.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../World/Chunk/ChunkSection.h"

void RenderMaster::drawSFML(const sf::Drawable &drawable)
{
    // m_sfmlRenderer.add(drawable);
}

void RenderMaster::drawChunk(const ChunkSection &chunk)
{
    const auto &solidMesh = chunk.getMeshes().solidMesh;
    const auto &waterMesh = chunk.getMeshes().waterMesh;
    const auto &floraMesh = chunk.getMeshes().floraMesh;

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

void RenderMaster::finishRender(sf::Window &window, const Camera &camera)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    m_chunkRenderer.render(camera);
    m_waterRenderer.render(camera);
    m_floraRenderer.render(camera);

    if (m_drawBox) {
        glDisable(GL_CULL_FACE);
        m_skyboxRenderer.render(camera);
        m_drawBox = false;
    }

    // m_sfmlRenderer  .render (window);

    window.display();
}
