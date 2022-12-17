#include "SFMLRenderer.h"

#include <glad/glad.h>


void SFMLRenderer::add(const sf::Drawable &drawable)
{
    m_draws.push_back(&drawable);
}