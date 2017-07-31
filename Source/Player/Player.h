#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Entity.h"
#include "../Item/ItemStack.h"
#include "../ToggleKey.h"

class World;
class RenderMaster;

class Player : public Entity
{
    public:
        Player();

        void handleInput(const sf::RenderWindow& window);

        void update(float dt, World& wolrd);
        void collide(World& world, const glm::vec3& vel, float dt);

        void addItem(const Material& material);

        void draw(RenderMaster& master);

        ItemStack& getHeldItems();

    private:
        void keyboardInput();
        void mouseInput(const sf::RenderWindow& window);
        bool m_isOnGround = false;

        std::vector<ItemStack> m_items;
        std::vector<sf::Text>  m_itemText;
        int m_heldItem = 0;

        ToggleKey m_itemDown;
        ToggleKey m_itemUp;
};



#endif // PLAYER_H_INCLUDED
