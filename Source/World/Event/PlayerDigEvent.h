#ifndef PLAYERDIGEVENT_H_INCLUDED
#define PLAYERDIGEVENT_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "../../Maths/glm.h"
#include "IWorldEvent.h"

class Player;

class PlayerDigEvent : public IWorldEvent {
  public:
    PlayerDigEvent(sf::Mouse::Button button, const glm::vec3 &location,
                   Player &player);

    void handle(World &world);

  private:
    void dig(World &world);

    sf::Mouse::Button m_buttonPress;
    glm::vec3 m_digSpot;
    Player *m_pPlayer;
};

#endif // PLAYERDIGEVENT_H_INCLUDED
