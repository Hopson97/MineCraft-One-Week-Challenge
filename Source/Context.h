#pragma once

#include <SFML/Window/Window.hpp>

#include "Config.h"

/// @brief Struct related to window and application context.
struct Context {
    Context(const Config &config);

    sf::Window window;
};
