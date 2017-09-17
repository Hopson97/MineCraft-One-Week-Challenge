#ifndef RENDERMASTER_H_INCLUDED
#define RENDERMASTER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "SkyboxRenderer.h"
#include "SFMLRenderer.h"
#include "WaterRenderer.h"
#include "../Config.h"


class Camera;
class ChunkSection;

class RenderMaster
{
    public:
        void drawSFML(const sf::Drawable& drawable);
        void drawQuad(const glm::vec3& pos);
        void drawCube(const Entity& cube);
        void drawChunk(const ChunkSection& chunk);
        void drawSky();

        void setConfig(const Config con);

        void finishRender(sf::RenderWindow& window, const Camera& camera);

    private:
        QuadRenderer    m_quadRenderer;
        CubeRenderer    m_cubeRenderer;
        ChunkRenderer   m_chunkRenderer;
        WaterRenderer   m_waterRenderer;
        SkyboxRenderer  m_skyboxRenderer;
        SFMLRenderer    m_sfmlRenderer;

        Config m_conf;

        bool m_drawBox = false;
};



#endif // RENDERMASTER_H_INCLUDED
