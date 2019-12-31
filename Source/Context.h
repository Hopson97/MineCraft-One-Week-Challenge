#pragma once

#include <SFML/Window/Window.hpp>

#include "Config.h"

struct Context {
    Context(const Config &config);

    sf::Window window;
};
