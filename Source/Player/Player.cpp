#include "Player.h"

#include <SFML/Graphics.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "../Input/Keyboard.h"
#include "../Renderer/RenderMaster.h"
#include "../World/World.h"
#include <imgui.h>

Player::Player()
    : Entity({2500, 125, 2500}, {0.f, 0.f, 0.f}, {0.3f, 1.f, 0.3f})
    , m_itemDown(sf::Keyboard::Key::Down)
    , m_itemUp(sf::Keyboard::Key::Up)
    , m_flyKey(sf::Keyboard::Key::F)
    , m_num1(sf::Keyboard::Key::Num1)
    , m_num2(sf::Keyboard::Key::Num2)
    , m_num3(sf::Keyboard::Key::Num3)
    , m_num4(sf::Keyboard::Key::Num4)
    , m_num5(sf::Keyboard::Key::Num5)
    , m_slow(sf::Keyboard::Key::LShift)
    , m_acceleration(glm::vec3(0.f))
{

    for (int i = 0; i < 5; i++)
    {
        m_items.emplace_back(Material::NOTHING, 0);
    }
}

void Player::addItem(const Material& material)
{
    Material::ID id = material.id;

    for (unsigned i = 0; i < m_items.size(); i++)
    {
        if (m_items[i].getMaterial().id == id)
        {
            /*int leftOver =*/m_items[i].add(1);

            return;
        }
        else if (m_items[i].getMaterial().id == Material::ID::Nothing)
        {
            m_items[i] = {material, 1};
            return;
        }
    }
}

ItemStack& Player::getHeldItems()
{
    return m_items[m_heldItem];
}

void Player::handleInput(const sf::Window& window, const Keyboard& keyboard)
{
    keyboardInput(keyboard);
    mouseInput(window);

    if (m_itemDown.isKeyPressed())
    {
        m_heldItem++;
        if (m_heldItem == (int)m_items.size())
        {
            m_heldItem = 0;
        }
    }
    else if (m_itemUp.isKeyPressed())
    {
        m_heldItem--;
        if (m_heldItem == -1)
        {
            m_heldItem = m_items.size() - 1;
        }
    }

    if (m_flyKey.isKeyPressed())
    {
        m_isFlying = !m_isFlying;
    }

    if (m_num1.isKeyPressed())
    {
        m_heldItem = 0;
    }
    if (m_num2.isKeyPressed())
    {
        m_heldItem = 1;
    }
    if (m_num3.isKeyPressed())
    {
        m_heldItem = 2;
    }
    if (m_num4.isKeyPressed())
    {
        m_heldItem = 3;
    }
    if (m_num5.isKeyPressed())
    {
        m_heldItem = 4;
    }
    if (m_slow.isKeyPressed())
    {
        m_isSneak = !m_isSneak;
    }
}

void Player::update(float dt, World& world)
{
    velocity += m_acceleration;
    m_acceleration = {0, 0, 0};

    if (!m_isFlying)
    {
        if (!m_isOnGround)
        {
            velocity.y -= 40 * dt;
        }
        m_isOnGround = false;
    }

    if (position.y <= 0 && !m_isFlying)
    {
        position.y = 300;
    }

    position.x += velocity.x * dt;
    collide(world, {velocity.x, 0, 0}, dt);

    position.y += velocity.y * dt;
    collide(world, {0, velocity.y, 0}, dt);

    position.z += velocity.z * dt;
    collide(world, {0, 0, velocity.z}, dt);

    box.update(position);
    velocity.x *= 0.95f;
    velocity.z *= 0.95f;
    if (m_isFlying)
    {
        velocity.y *= 0.95f;
    }
}

void Player::collide(World& world, const glm::vec3& vel, float dt)
{
    for (int x = position.x - box.dimensions.x; x < position.x + box.dimensions.x; x++)
        for (int y = position.y - box.dimensions.y; y < position.y + 0.7; y++)
            for (int z = position.z - box.dimensions.z; z < position.z + box.dimensions.z; z++)
            {
                auto block = world.getBlock(x, y, z);

                if (block != 0 && block.getData().isCollidable)
                {
                    if (vel.y > 0)
                    {
                        position.y = y - box.dimensions.y;
                        velocity.y = 0;
                    }
                    else if (vel.y < 0)
                    {
                        m_isOnGround = true;
                        position.y = y + box.dimensions.y + 1;
                        velocity.y = 0;
                    }

                    if (vel.x > 0)
                    {
                        position.x = x - box.dimensions.x;
                    }
                    else if (vel.x < 0)
                    {
                        position.x = x + box.dimensions.x + 1;
                    }

                    if (vel.z > 0)
                    {
                        position.z = z - box.dimensions.z;
                    }
                    else if (vel.z < 0)
                    {
                        position.z = z + box.dimensions.z + 1;
                    }
                }
            }
}

///@TODO Move this
float speed = 0.2f;

void Player::keyboardInput(const Keyboard& keyboard)
{
    if (keyboard.isKeyDown(sf::Keyboard::Key::W))
    {
        float s = speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
            s *= 5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
            s *= 0.35f;
        m_acceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * s;
        m_acceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * s;
    }
    if (keyboard.isKeyDown(sf::Keyboard::Key::S))
    {
        m_acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
        m_acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (keyboard.isKeyDown(sf::Keyboard::Key::A))
    {
        m_acceleration.x += -glm::cos(glm::radians(rotation.y)) * speed;
        m_acceleration.z += -glm::sin(glm::radians(rotation.y)) * speed;
    }
    if (keyboard.isKeyDown(sf::Keyboard::Key::D))
    {
        m_acceleration.x += glm::cos(glm::radians(rotation.y)) * speed;
        m_acceleration.z += glm::sin(glm::radians(rotation.y)) * speed;
    }

    if (keyboard.isKeyDown(sf::Keyboard::Key::Space))
    {
        jump();
    }
    else if (keyboard.isKeyDown(sf::Keyboard::Key::LShift) && m_isFlying)
    {
        m_acceleration.y -= speed * 3;
    }
}

void Player::mouseInput(const sf::Window& window)
{
    static bool useMouse = true;
    static ToggleKey useMouseKey(sf::Keyboard::Key::L);

    if (useMouseKey.isKeyPressed())
    {
        useMouse = !useMouse;
    }

    if (!useMouse)
    {
        return;
    }

    static float const BOUND = 89.f;
    static auto lastMousePosition = sf::Mouse::getPosition(window);
    auto change = sf::Mouse::getPosition() - lastMousePosition;

    rotation.y += change.x * 0.05f;
    rotation.x += change.y * 0.05f;

    if (rotation.x > BOUND)
        rotation.x = BOUND;
    else if (rotation.x < -BOUND)
        rotation.x = -BOUND;

    if (rotation.y > 360)
        rotation.y = 0;
    else if (rotation.y < 0)
        rotation.y = 360;

    auto cx = static_cast<int>(window.getSize().x / 2);
    auto cy = static_cast<int>(window.getSize().y / 2);

    sf::Mouse::setPosition({cx, cy}, window);

    lastMousePosition = sf::Mouse::getPosition();
}

void Player::draw(RenderMaster& master)
{
    if (ImGui::Begin("Player"))
    {

        for (unsigned i = 0; i < m_items.size(); i++)
        {
            ImGui::Text("%s %d", m_items[i].getMaterial().name.c_str(), m_items[i].getNumInStack());
        }
        ImGui::Text("X: %.2f, Y: %.2f, z: %.2f", position.x, position.y, position.z);
    }
    ImGui::End();
}

void Player::jump()
{
    if (!m_isFlying)
    {
        if (m_isOnGround)
        {

            m_isOnGround = false;
            m_acceleration.y += speed * 50;
        }
    }
    else
    {
        m_acceleration.y += speed * 3;
    }
}
