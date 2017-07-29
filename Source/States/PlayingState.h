#ifndef PLAYINGSTATE_H_INCLUDED
#define PLAYINGSTATE_H_INCLUDED

#include "StateBase.h"
#include "../Player/Player.h"

#include "../World/Chunk/Chunk.h"
#include "../World/World.h"

class StatePlaying : public StateBase
{
    public:
        StatePlaying(Application& app);

        void handleEvent(sf::Event e);
        void handleInput();

        void update(float deltaTime);

        void render(RenderMaster& renderer);

    private:
        Player m_player;

        World m_world;
};

#endif // PLAYINGSTATE_H_INCLUDED
