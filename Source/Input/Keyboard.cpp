#include "Keyboard.h"

Keyboard::Keyboard()
{
    std::fill(m_keys.begin(), m_keys.end(), false);
}

void Keyboard::update(sf::Event e)
{
    m_recentlyReleased = sf::Keyboard::KeyCount;
    switch (e.type) {
        case sf::Event::KeyReleased:
            m_keys[e.key.code] = false;
            break;

        case sf::Event::KeyPressed:
            m_recentlyReleased = e.key.code;
            m_keys[e.key.code] = true;
            break;

        default:
            break;
    }
}

bool Keyboard::isKeyDown(sf::Keyboard::Key key) const
{
    return m_keys[key];
}

bool Keyboard::keyReleased(sf::Keyboard::Key key) const
{
    return m_recentlyReleased == key;
}