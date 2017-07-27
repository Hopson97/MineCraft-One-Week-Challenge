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
    static sf::Clock c;
    static float lastTime = 0;
    float timeNow = c.getElapsedTime().asSeconds();
    auto dt =  timeNow - lastTime;
    lastTime = timeNow;



    renderer.drawQuad({0, 0, std::sin(timeNow) * 3});
}
