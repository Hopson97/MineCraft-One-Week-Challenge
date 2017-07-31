#include "RenderMaster.h"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../World/Chunk/ChunkMesh.h"

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

void RenderMaster::drawChunk(const ChunkMesh& mesh)
{
    if (mesh.faces > 0)
        m_chunkRenderer.add(mesh);
}

void RenderMaster::drawSky()
{
    m_drawBox = true;
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
    glClearColor(0.1, 0.5, 1.0, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_quadRenderer  .render (camera);
    m_cubeRenderer  .render (camera);
    m_chunkRenderer .render (camera);

    if (m_drawBox)
    {
        glDisable(GL_CULL_FACE);
        m_skyboxRenderer.render (camera);
        m_drawBox = false;
    }

    m_sfmlRenderer  .render (window);

    window.display();
}
