#include "Player.h"

#include <SFML/Graphics.hpp>

Player::Player()
{
    position = {0, 0, -5};
}

void Player::handleInput(const sf::RenderWindow& window)
{
    keyboardInput();
    mouseInput(window);
}

void Player::update(float dt)
{
    position += m_velocity * dt;
    m_velocity *= 0.95;
}

void Player::keyboardInput()
{
    glm::vec3 change;
    float speed = 0.5;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.x = glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z = glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.x = -glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z = -glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x = glm::cos(glm::radians(rotation.y)) * speed;
        change.z = glm::sin(glm::radians(rotation.y)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x = -glm::cos(glm::radians(rotation.y)) * speed;
        change.z = -glm::sin(glm::radians(rotation.y)) * speed;
    }

    m_velocity += change;
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

    auto cx = static_cast<int>(window.getSize().x / 4);
    auto cy = static_cast<int>(window.getSize().y / 4);

    sf::Mouse::setPosition({cx, cy}, window);

    lastMousePosition = sf::Mouse::getPosition();
}


























