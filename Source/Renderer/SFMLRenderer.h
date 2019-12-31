#ifndef SFMLRENDERER_H_INCLUDED
#define SFMLRENDERER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class SFMLRenderer {
  public:
    void add(const sf::Drawable &drawable);

    void render(sf::Window &window);

  private:
    std::vector<const sf::Drawable *> m_draws;
};

#endif // SFMLRENDERER_H_INCLUDED
