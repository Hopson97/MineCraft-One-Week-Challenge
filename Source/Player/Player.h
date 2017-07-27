#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../Entity.h"

class Player : public Entity
{
    public:
        Player();

        void handleInput();

        void update(float dt);

    private:
        void keyboardInput();
        void mouseInput();
};



#endif // PLAYER_H_INCLUDED
