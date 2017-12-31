#ifndef RENDERMASTER_H_INCLUDED
#define RENDERMASTER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "../PostProcess/PostProcessRenderer.h"
#include "ChunkRenderer.h"
#include "SFMLRenderer.h"
#include "WaterRenderer.h"
#include "FloraRenderer.h"
#include "../Config.h"
#include "../Sky/SkyManager.h"


#include "../States/PlayingState.h"
#include "../PostProcess/Framebuffer.h"

class Camera;
class ChunkSection;

class RenderMaster
{
    public:
        RenderMaster();

        void drawSFML(const sf::Drawable& drawable);
        void drawChunk(const ChunkSection& chunk);
        void drawSky();

        void finishRender(sf::RenderWindow& window, const Camera& camera);

    private:

        //Primitives
        PostProcessRender   m_postRenderer;

        //Chunks
        ChunkRenderer   m_chunkRenderer;
        WaterRenderer   m_waterRenderer;
        FloraRenderer   m_floraRenderer;

        //Detail
        SFMLRenderer    m_sfmlRenderer;
        
        FrameBufferObject fbo;

        bool m_drawBox = false;
};



#endif // RENDERMASTER_H_INCLUDED
