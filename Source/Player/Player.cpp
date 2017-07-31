#include "Player.h"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../World/World.h"

#include "../Renderer/RenderMaster.h"

sf::Font f;

Player::Player()
:   Entity  ({25, 125, 25}, {0, 0, 0}, {0.5, 1.5, 0.5})
{
    f.loadFromFile("Res/Fonts/rs.ttf");

    for (int i = 0; i < 5; i++)
    {
        m_items.emplace_back(Material::NOTHING, 0);
    }

    for (int i = 0; i < 5; i++)
    {
        sf::Text t;
        t.setFont(f);
        t.setOutlineColor(sf::Color::Black);
        t.setCharacterSize(25);
        t.setPosition({20, 20 * i + 100});
        m_itemText.push_back(t);
    }
}

void Player::addItem(Material& material)
{

}



void Player::handleInput(const sf::RenderWindow& window)
{
    keyboardInput();
    mouseInput(window);
}

void Player::update(float dt, World& world)
{
/*
    if (!m_isOnGround)
    {
        velocity.y -= 55 * dt;
    }
*/
    m_isOnGround = false;

    box.update(position);
    velocity.x *= 0.95;
    velocity.z *= 0.95;
    velocity.y *= 0.95;

    position.x += velocity.x * dt;
    //collide (world, {velocity.x, 0, 0}, dt);

    position.y += velocity.y * dt;
    //collide (world, {0, velocity.y, 0}, dt);

    position.z += velocity.z * dt;
    //collide (world, {0, 0, velocity.z}, dt);
}


void Player::collide(World& world, const glm::vec3& vel, float dt)
{
    for (int x = position.x - box.dimensions.x; x < position.x + box.dimensions.x   ; x++)
    for (int y = position.y - box.dimensions.y; y < position.y + box.dimensions.y   ; y++)
    for (int z = position.z - box.dimensions.z; z < position.z + box.dimensions.z   ; z++)
    {
        auto block = world.getBlock(x, y, z);

        if (block != 0)
        {
            if (vel.x > 0)
            {
                position.x = x - box.dimensions.x;
            }
            if (vel.x < 0)
            {
                position.x = x + box.dimensions.x + 1;
            }

            if (vel.y > 0)
            {
                position.y = y - box.dimensions.y;
                velocity.y = 0;
            }
            if (vel.y < 0)
            {
                position.y = y + box.dimensions.y + 1;
                velocity.y = 0;
                m_isOnGround = true;
            }

            if (vel.z > 0)
            {
                position.z = z - box.dimensions.z;
            }
            if (vel.x < 0)
            {
                position.z = z + box.dimensions.z + 1;
            }
        }
    }
}


void Player::keyboardInput()
{
    glm::vec3 change;
    float speed = 0.8;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        speed *= 8;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x += -glm::cos(glm::radians(rotation.y)) * speed;
        change.z += -glm::sin(glm::radians(rotation.y)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x += glm::cos(glm::radians(rotation.y)) * speed;
        change.z += glm::sin(glm::radians(rotation.y)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        change.y += speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        change.y -= speed;
    }

    velocity += change;
}

void Player::mouseInput(const sf::RenderWindow& window)
{
    static auto const BOUND = 80;
    static auto lastMousePosition = sf::Mouse::getPosition(window);
    auto change = sf::Mouse::getPosition() - lastMousePosition;

    rotation.y += change.x * 0.05;
    rotation.x += change.y * 0.05;

    if      (rotation.x >  BOUND) rotation.x =  BOUND;
    else if (rotation.x < -BOUND) rotation.x = -BOUND;

    if      (rotation.y >  360) rotation.y = 0;
    else if (rotation.y < 0)    rotation.y = 360;

    auto cx = static_cast<int>(window.getSize().x / 2);
    auto cy = static_cast<int>(window.getSize().y / 2);

    sf::Mouse::setPosition({cx, cy}, window);

    lastMousePosition = sf::Mouse::getPosition();
}

void Player::draw(RenderMaster& master)
{
    for (int i = 0; i < m_items.size(); i++)
    {
        sf::Text& t = m_itemText[i];
        if (i == m_heldItem)
        {
            t.setFillColor(sf::Color::Red);
        }
        else
        {
            t.setFillColor(sf::Color::White);
        }
        t.setString((m_items[i].getMaterial().name));
        master.drawSFML(t);
    }
}


























