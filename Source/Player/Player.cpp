#include "Player.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <iomanip>

#include "../World/World.h"

#include "../Renderer/RenderMaster.h"

sf::Font f;

Player::Player()
:   Entity  ({2500, 125, 2500}, {0, 0, 0}, {0.3, 1.0, 0.3})
,   m_itemDown  (sf::Keyboard::Down)
,   m_itemUp    (sf::Keyboard::Up)
,   m_flyKey    (sf::Keyboard::F)
{
    for (int i = 0; i < 5; i++)
    {
        m_inventoryJumps.emplace_back
            ((sf::Keyboard::Key(sf::Keyboard::Num1 + i)));
    }


    f.loadFromFile("Res/Fonts/rs.ttf");


    for (int i = 0; i < 5; i++)
    {
        m_items.emplace_back(Material::NOTHING, 0);
    }

    for (float i = 0; i < 5; i++)
    {
        sf::Text t;
        t.setFont(f);
        t.setOutlineColor(sf::Color::Black);
        t.setCharacterSize(25);
        t.setPosition({20.0f, 20.0f * i + 100.0f});
        m_itemText.push_back(t);
    }
    m_posPrint.setFont(f);
    m_posPrint.setOutlineColor(sf::Color::Black);
    m_posPrint.setCharacterSize(25);
    m_posPrint.setPosition(20.0f, 20.0f * 6.0f + 100.0f);
}

void Player::addItem(const Material& material)
{
    Material::ID id = material.id;

    for (unsigned i = 0; i < m_items.size(); i++)
    {
        if (m_items[i].getMaterial().id == id)
        {
            /*int leftOver =*/ m_items[i].add(1);

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


void Player::handleInput(const sf::RenderWindow& window)
{
    keyboardInput();
    mouseInput(window);

    if(m_itemDown.isKeyPressed())
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

    for (int i = 0; i < 5; i++)
    {
        if(m_inventoryJumps[i].isKeyPressed())
        {
            m_heldItem = i;
        }
    }

    if (m_flyKey.isKeyPressed())
    {
        m_isFlying = !m_isFlying;
    }
}

void Player::update(float dt, World& world)
{
    velocity += m_acceleation;
    m_acceleation = {0, 0, 0};

    if (!m_isFlying)
    {
        if (!m_isOnGround)
        {
            velocity.y -= 40 * dt;
        }
        m_isOnGround = false;
    }


    position.x += velocity.x * dt;
    collide (world, {velocity.x, 0, 0}, dt);

    position.y += velocity.y * dt;
    collide (world, {0, velocity.y, 0}, dt);

    position.z += velocity.z * dt;
    collide (world, {0, 0, velocity.z}, dt);


    box.update(position);
    velocity.x *= 0.95;
    velocity.z *= 0.95;
    if (m_isFlying)
    {
        velocity.y *= 0.95;
    }
}


void Player::collide(World& world, const glm::vec3& vel, float dt)
{
    for (int x = position.x - box.dimensions.x; x < position.x + box.dimensions.x; x++)
    for (int y = position.y - box.dimensions.y; y < position.y + 0.7             ; y++)
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


void Player::keyboardInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        float s = speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) 
        {
            if (m_isFlying) s *= 5;
            else s *= 1.75;
        }
        m_acceleation.x += -glm::cos(glm::radians(rotation.y + 90)) * s;
        m_acceleation.z += -glm::sin(glm::radians(rotation.y + 90)) * s;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_acceleation.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
        m_acceleation.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_acceleation.x += -glm::cos(glm::radians(rotation.y)) * speed;
        m_acceleation.z += -glm::sin(glm::radians(rotation.y)) * speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_acceleation.x += glm::cos(glm::radians(rotation.y)) * speed;
        m_acceleation.z += glm::sin(glm::radians(rotation.y)) * speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        jump();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && m_isFlying)
    {
        m_acceleation.y -= speed * 3;
    }
}

void Player::mouseInput(const sf::RenderWindow& window)
{
    static bool useMouse = true;
    static ToggleKey useMouseKey (sf::Keyboard::L);

    if (useMouseKey.isKeyPressed())
    {
        useMouse = !useMouse;
    }

    if (!useMouse)
    {
        return;
    }

	 static sf::Vector2i center = {
		 static_cast<int>(window.getSize().x / 2),
		 static_cast<int>(window.getSize().y / 2)
	 };

    static auto const BOUND = 89.9999;
    static auto lastMousePosition = sf::Mouse::getPosition(window);
    auto change = sf::Mouse::getPosition(window) - lastMousePosition;

    rotation.y += change.x * 0.05;
    rotation.x += change.y * 0.05;

    if      (rotation.x >  BOUND) rotation.x =  BOUND;
    else if (rotation.x < -BOUND) rotation.x = -BOUND;

    if      (rotation.y >  360) rotation.y = 0;
    else if (rotation.y <  0)   rotation.y = 360;

    lastMousePosition = sf::Mouse::getPosition(window);

	 if(lastMousePosition.x < 10 || lastMousePosition.x > window.getSize().x - 10 || lastMousePosition.y < 10 || lastMousePosition.y > window.getSize().y - 10 ) {
		sf::Mouse::setPosition( center );
		lastMousePosition = center;
	 }
}

void Player::draw(RenderMaster& master)
{
    for (unsigned i = 0; i < m_items.size(); i++)
    {
        sf::Text& t = m_itemText[i];
        if (i == (unsigned)m_heldItem)
        {
            t.setFillColor(sf::Color::Red);
        }
        else
        {
            t.setFillColor(sf::Color::White);
        }
        t.setString((m_items[i].getMaterial().name) + " " + std::to_string(m_items[i].getNumInStack()) + " ");
        master.drawSFML(t);
    }
    std::ostringstream stream;
    stream  << " X: " << position.x
            << " Y: " << position.y
            << " Z: " << position.z
            << " Grounded " << std::boolalpha << m_isOnGround;

    m_posPrint.setString(stream.str());

    master.drawSFML(m_posPrint);
}

void Player::jump()
{
    if (!m_isFlying)
    {
        if (m_isOnGround)
        {
            m_isOnGround = false;
            m_acceleation.y += speed * 50;
        }
    }
    else
    {
        m_acceleation.y += speed * 3;
    }
}






