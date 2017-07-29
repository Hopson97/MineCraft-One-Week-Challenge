#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "Chunk/Chunk.h"

class RenderMaster;

class World : IChunk
{
    public:
        World();

        ChunkBlock  getBlock    (int x, int y, int z) const             override;
        void        setBlock    (int x, int y, int z, ChunkBlock block) override;

        void renderWorld(RenderMaster& master);

    private:
        std::vector<Chunk> m_chunks;
};

#endif // WORLD_H_INCLUDED
