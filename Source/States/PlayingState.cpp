#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"
#include "../Application.h"

#include "../World/Chunk/ChunkMeshBuilder.h"

#include <iostream>

StatePlaying::StatePlaying(Application& app)
:   StateBase   (app)
{
    app.getCamera().hookEntity(m_player);

    ChunkMeshBuilder builder(m_chunkTest);
    builder.buildMesh(m_chunkTest.mesh);

    m_chunkTest.mesh.bufferMesh();
}

void StatePlaying::handleEvent(sf::Event e)
{ }

void StatePlaying::handleInput()
{
    m_player.handleInput(m_pApplication->getWindow());
}

void StatePlaying::update(float deltaTime)
{
    m_player.update(deltaTime);
}

void StatePlaying::render(RenderMaster& renderer)
{
    renderer.drawCube({-1.1, 0, -1.1});
    renderer.drawChunk(m_chunkTest.mesh);
}
