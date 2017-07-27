#ifndef RENDERMASTER_H_INCLUDED
#define RENDERMASTER_H_INCLUDED

#include "QuadRenderer.h"

#include <SFML/Graphics.hpp>

class Camera;

class RenderMaster
{
    public:
        void drawQuad(const glm::vec3& pos);

        void finishRender(sf::RenderWindow& window, const Camera& camera);

    private:
        QuadRenderer m_quadRenderer;
};



#endif // RENDERMASTER_H_INCLUDED
