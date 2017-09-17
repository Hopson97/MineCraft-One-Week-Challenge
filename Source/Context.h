#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Config.h"

extern unsigned int g_X;
extern unsigned int g_Y;

struct Context
{
    Context(const Config& config);

    sf::RenderWindow window;
};

#endif // CONTEXT_H_INCLUDED
