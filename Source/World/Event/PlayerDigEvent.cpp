#include "PlayerDigEvent.h"

#include "../World.h"
#include "../../Item/Material.h"
#include "../../Player/Player.h"

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
            auto block = world.getBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z);
            const auto& material = Material::toMaterial((BlockId)block.id);
            m_pPlayer->addItem(material);
            world.updateChunk   (m_digSpot.x, m_digSpot.y, m_digSpot.z);
            world.setBlock      (m_digSpot.x, m_digSpot.y, m_digSpot.z, 0);
            break;
        }

        case sf::Mouse::Button::Right:{
            auto& stack = m_pPlayer->getHeldItems();
            auto& material = stack.getMaterial();

            if (material.id == Material::ID::Nothing)
            {
                return;
            }
            else
            {
                stack.remove();
                world.updateChunk   (m_digSpot.x, m_digSpot.y, m_digSpot.z);
                world.setBlock      (m_digSpot.x, m_digSpot.y, m_digSpot.z, material.toBlockID());
                break;
            }
        }
        default:
            break;
    }
}
