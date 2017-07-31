#include "PlayerDigEvent.h"

#include "../World.h"

PlayerDigEvent::PlayerDigEvent(sf::Mouse::Button button, const glm::vec3& location, Player& player)
:   m_buttonPress   (button)
,   m_digSpot       (location)
,   m_pPlayer       (&player)
{ }

void PlayerDigEvent::handle(World& world)
{
    auto chunkLocation = World::getChunkXZ(m_digSpot.x, m_digSpot.z);
    if (world.getChunkManager().chunkLoadedAt(chunkLocation.x, chunkLocation.z))
    {
        dig(world);
    }
}

void PlayerDigEvent::dig(World& world)
{
    switch (m_buttonPress)
    {
        case sf::Mouse::Button::Left:{
            ///@TODO Use player tool
            world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, 0);
            break;
        }

        case sf::Mouse::Button::Right:{
            ///@TODO Use player held item
            world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, 1);
            break;
        }
        default:
            break;
    }
}
