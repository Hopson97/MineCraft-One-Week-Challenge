#ifndef TOGGLEKEY_H_INCLUDED
#define TOGGLEKEY_H_INCLUDED

#include <SFML/Graphics.hpp>

class ToggleKey
{
    public:
        ToggleKey(sf::Keyboard::Key);

        bool isKeyPressed();

    private:
        sf::Keyboard::Key m_key;
        sf::Clock m_delayTimer;

};

#endif // TOGGLEKEY_H_INCLUDED
