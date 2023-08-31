#include "MenuState.h"

#include "../Application.h"
#include "../Renderer/RenderMaster.h"

#include <iostream>

MenuState::MenuState(Application &app, const Config &config) :
    StateBase(app)
{

}

void MenuState::handleEvent(sf::Event e)
{
    m_keyboard.update(e);
}

void MenuState::onOpen()
{
    m_Application.turnOnMouse();
}