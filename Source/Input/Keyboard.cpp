#include "Keyboard.h"

#include <iostream>

Keyboard::Keyboard()
{
    std::fill(m_keys.begin(), m_keys.end(), false);
}

void Keyboard::update(sf::Event e)
{
    if (auto* key = e.getIf<sf::Event::KeyPressed>())
    {
        if ((size_t)key->code < m_keys.size())
        {
            m_keys[(size_t)key->code] = true;
        }
    }
    else if (auto* key = e.getIf<sf::Event::KeyReleased>())
    {
        m_recentlyReleased = key->code;
        if ((size_t)key->code < m_keys.size())
        {
            m_keys[(size_t)key->code] = false;
        }
    }
}

bool Keyboard::isKeyDown(sf::Keyboard::Key key) const
{
    return m_keys[(size_t)key];
}

bool Keyboard::keyReleased(sf::Keyboard::Key key) const
{
    return m_recentlyReleased == key;
}