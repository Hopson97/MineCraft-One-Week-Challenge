#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"

class RenderMaster;
class Camera;

class World
{
    public:
        World();

        ChunkBlock  getBlock    (int x, int y, int z);
        void        setBlock    (int x, int y, int z, ChunkBlock block);

        void update(const Camera& camera);

        void renderWorld(RenderMaster& master);

    private:
        ChunkManager m_chunkManager;
        std::unordered_set<sf::Vector3i> m_rebuildChunks;
};

#endif // WORLD_H_INCLUDED
