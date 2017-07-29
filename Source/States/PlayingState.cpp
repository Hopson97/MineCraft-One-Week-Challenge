#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"
#include "../Application.h"

#include "../World/Chunk/ChunkMeshBuilder.h"
#include "../Maths/Ray.h"

#include <iostream>

StatePlaying::StatePlaying(Application& app)
:   StateBase   (app)
{
    app.getCamera().hookEntity(m_player);
}

void StatePlaying::handleEvent(sf::Event e)
{ }

void StatePlaying::handleInput()
{
    m_player.handleInput(m_pApplication->getWindow());

    static sf::Clock timer;
    glm::vec3 lastPosition;

    for (Ray ray(m_player.position, m_player.rotation);
             ray.getLength() < 6;
             ray.step(0.1))
    {
        int x = ray.getEnd().x;
        int y = ray.getEnd().y;
        int z = ray.getEnd().z;

        auto block = m_world.getBlock(x, y, z);

        if(block != 0)
        {
            if (timer.getElapsedTime().asSeconds() > 0.2)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    timer.restart();
                    m_world.editBlock(x, y, z, 0);
                    break;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    timer.restart();
                    m_world.editBlock(lastPosition.x,
                                      lastPosition.y,
                                      lastPosition.z, 1);
                    break;
                }
            }
        }
        lastPosition = ray.getEnd();
    }
}

void StatePlaying::update(float deltaTime)
{
    m_player.update(deltaTime);
}

void StatePlaying::render(RenderMaster& renderer)
{
    renderer.drawCube({-1.1, 0, -1.1});
    m_world.renderWorld(renderer);
}
