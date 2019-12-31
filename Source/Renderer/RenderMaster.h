#ifndef RENDERMASTER_H_INCLUDED
#define RENDERMASTER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "../Config.h"
#include "ChunkRenderer.h"
#include "FloraRenderer.h"
#include "SFMLRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"

class Camera;
class ChunkSection;

class RenderMaster {
  public:
    void drawSFML(const sf::Drawable &drawable);
    void drawChunk(const ChunkSection &chunk);
    void drawSky();

    void finishRender(sf::Window &window, const Camera &camera);

  private:
    // Chunks
    ChunkRenderer m_chunkRenderer;
    WaterRenderer m_waterRenderer;
    FloraRenderer m_floraRenderer;

    // Detail
    SkyboxRenderer m_skyboxRenderer;
    // SFMLRenderer    m_sfmlRenderer;

    bool m_drawBox = false;
};

#endif // RENDERMASTER_H_INCLUDED
