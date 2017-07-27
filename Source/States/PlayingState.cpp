#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"

StatePlaying::StatePlaying(Application& app)
:   StateBase   (app)
{

}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(float deltaTime)
{

}

void StatePlaying::render(RenderMaster& renderer)
{
    renderer.drawQuad({0, 0, 0});
}
