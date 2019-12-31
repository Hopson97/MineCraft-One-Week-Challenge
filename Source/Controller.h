#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "Maths/glm.h"
#include <SFML/Graphics.hpp>

// WIP
class Controller {
    glm::vec3 translateInput();
    sf::Vector2i mouseInput();
};

#endif // CONTROLLER_H_INCLUDED
