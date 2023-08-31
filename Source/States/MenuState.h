#ifndef MENUSTATE_H_INCLUDED
#define MENUSTATE_H_INCLUDED

#include "../Player/Player.h"
#include "StateBase.h"

#include "../Input/Keyboard.h"

class MenuState : public StateBase
{
public:
    MenuState(Application &app, const Config &config);
    ~MenuState();

    void handleEvent(sf::Event e) override;
    void handleInput() override;

    void update(float deltaTime) override;

    void render(RenderMaster &renderer) override;

    void onOpen() override;

private:
    Keyboard m_keyboard;
    Player m_player;
    World m_world;
};

#endif