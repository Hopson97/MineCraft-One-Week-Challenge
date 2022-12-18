#ifndef TOGGLEKEY_H_INCLUDED
#define TOGGLEKEY_H_INCLUDED

#include <SFML/Graphics.hpp>

/// @brief A keyboard related subclass that determines if a key remains pressed.
class ToggleKey {
  public:
    ToggleKey(sf::Keyboard::Key);

    bool isKeyPressed();

  private:
    sf::Keyboard::Key m_key;
    sf::Clock m_delayTimer;
};

#endif // TOGGLEKEY_H_INCLUDED
