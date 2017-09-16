#include "Context.h"

#include <GL/glew.h>

unsigned int g_X;
unsigned int g_Y;

Context::Context(const Config& config)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.depthBits = 24;
    settings.stencilBits = 8;

    if(config.isFullscreen)
    {
        window.create(sf::VideoMode::getDesktopMode(), "MineCraft Week", sf::Style::Fullscreen, settings);
        g_X = sf::VideoMode::getDesktopMode().width;
        g_Y = sf::VideoMode::getDesktopMode().height;
    }
    else
    {
        sf::VideoMode winMode(config.windowX, config.windowY);
        window.create(winMode, "MineCraft Week", sf::Style::Close, settings);
        g_X = config.windowX;
        g_Y = config.windowY;
    }

    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
