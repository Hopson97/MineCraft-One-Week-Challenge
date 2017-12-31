#ifndef CHUNKRENDERER_H_INCLUDED
#define CHUNKRENDERER_H_INCLUDED

#include <vector>

#include "../Shaders/ChunkShader.h"
#include "../Config.h"
#include "../World/Block/BlockDB.h"


struct RenderInfo;
class ChunkMesh;
class Camera;

class ChunkRenderer
{
    public:
        void add(const ChunkMesh& mesh);
        void render(const Camera& camera, Config* conf);

    private:
        std::vector<const RenderInfo*> m_chunks;

        ChunkShader m_shader;

};

#endif // CHUNKRENDERER_H_INCLUDED
