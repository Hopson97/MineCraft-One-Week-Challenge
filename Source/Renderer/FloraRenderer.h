#ifndef FLORARENDERER_H_INCLUDED
#define FLORARENDERER_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

#include "../Shaders/FloraShader.h"
#include "../Config.h"

struct RenderInfo;
class ChunkMesh;
class Camera;

class FloraRenderer
{
    public:
        void add(const ChunkMesh& mesh);
        void render(const Camera& camera, Config* conf);

    private:
        std::vector<const RenderInfo*> m_chunks;

        FloraShader m_shader;
};


#endif // FLORARENDERER_H_INCLUDED
