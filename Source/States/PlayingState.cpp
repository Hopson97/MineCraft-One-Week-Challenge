#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"
#include "../Application.h"

StatePlaying::StatePlaying(Application& app)
:   StateBase   (app)
{
    app.getCamera().hookEntity(m_player);
}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput()
{
    m_player.handleInput(m_pApplication->getWindow());
}

void StatePlaying::update(float deltaTime)
{
    m_player.update(deltaTime);
}

void StatePlaying::render(RenderMaster& renderer)
{
    renderer.drawQuad({0, 0, 0});
}
