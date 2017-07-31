#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class World;

class Player : public Entity
{
    public:
        Player();

        void handleInput(const sf::RenderWindow& window);

        void update(float dt, World& wolrd);
        void collide(World& world, const glm::vec3& vel, float dt);

    private:
        void keyboardInput();
        void mouseInput(const sf::RenderWindow& window);
        bool m_isOnGround = false;
};



#endif // PLAYER_H_INCLUDED
