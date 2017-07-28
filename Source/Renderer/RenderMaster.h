#ifndef RENDERMASTER_H_INCLUDED
#define RENDERMASTER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"

class Camera;
class ChunkMesh;

class RenderMaster
{
    public:
        void drawQuad(const glm::vec3& pos);
        void drawCube(const glm::vec3& pos);
        void drawChunk(const ChunkMesh& mesh);

        void finishRender(sf::RenderWindow& window, const Camera& camera);

    private:
        QuadRenderer m_quadRenderer;
        CubeRenderer m_cubeRenderer;
        ChunkRenderer m_chunkRenderer;
};



#endif // RENDERMASTER_H_INCLUDED
