#include "Application.h"

#include <SFML/Window/Event.hpp>
#include <imgui.h>
#include <iostream>

#include "Maths/Ray.h"
#include "Renderer/RenderMaster.h"
#include "World/Block/BlockDatabase.h"
#include "World/Event/PlayerDigEvent.h"
float g_timeElapsed = 0;

Application::Application(sf::Window& window, const Config& config)
    : m_window(window)
    , m_camera(config)
    , m_config(config)
    , m_world(m_camera, config, m_player)

{
    BlockDatabase::get();
    m_camera.hookEntity(m_player);
}

void Application::on_event(const sf::Event& event)
{
}

void Application::on_update(const Keyboard& keyboard, sf::Time dt)
{

    m_player.handleInput(m_window, keyboard);
    static sf::Clock timer;
    glm::vec3 lastPosition;

    // Ray is cast as player's 'vision'
    for (Ray ray({m_player.position.x, m_player.position.y + 0.6f, m_player.position.z},
                 m_player.rotation); // Corrected for camera offset
         ray.getLength() < 6; ray.step(0.05f))
    {
        int x = static_cast<int>(ray.getEnd().x);
        int y = static_cast<int>(ray.getEnd().y);
        int z = static_cast<int>(ray.getEnd().z);

        auto block = m_world.getBlock(x, y, z);
        auto id = (BlockId)block.id;

        if (id != BlockId::Air && id != BlockId::Water)
        {
            if (timer.getElapsedTime().asSeconds() > 0.2)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    timer.restart();
                    // The player "digs" the block up
                    m_world.addEvent<PlayerDigEvent>(sf::Mouse::Button::Left, ray.getEnd(),
                                                     m_player);
                    break;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                {
                    timer.restart();
                    // Block is placed by player
                    m_world.addEvent<PlayerDigEvent>(sf::Mouse::Button::Right, lastPosition,
                                                     m_player);
                    break;
                }
            }
        }
        lastPosition = ray.getEnd();
    }

    if (m_player.position.x < 0)
        m_player.position.x = 0;
    if (m_player.position.z < 0)
        m_player.position.z = 0;

    m_camera.update();
    m_player.update(dt.asSeconds(), m_world);
    m_world.update(m_camera);
}

void Application::on_render(bool show_debug_info)
{
    static sf::Clock dt;

    static bool drawGUI = false;
    static ToggleKey drawKey(sf::Keyboard::Key::F3);

    if (drawKey.isKeyPressed())
    {
        drawGUI = !drawGUI;
    }

    if (drawGUI)
    {
        m_player.draw(m_masterRenderer);
    }

    m_world.renderWorld(m_masterRenderer, m_camera);

    m_masterRenderer.finishRender(m_window, m_camera);
}
