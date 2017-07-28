#ifndef PLAYINGSTATE_H_INCLUDED
#define PLAYINGSTATE_H_INCLUDED

#include "StateBase.h"
#include "../Player/Player.h"

#include "../World/Chunk/ChunkSection.h"

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

        ChunkSection m_chunkTest;
};

#endif // PLAYINGSTATE_H_INCLUDED
