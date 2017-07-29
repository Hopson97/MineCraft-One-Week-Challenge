#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <vector>
#include "ChunkSection.h"

class RenderMaster;

class Chunk : public IChunk
{
    public:
        Chunk(World& world);

        void setBlock       (int x, int y, int z, ChunkBlock block) override;
        ChunkBlock getBlock (int x, int y, int z) const override;

        void drawChunks (RenderMaster& renderer);

    private:
        bool outOfBound(int x, int y, int z) const ;

        std::vector<ChunkSection> m_chunks;

        World* m_pWorld;
};

#endif // CHUNK_H_INCLUDED
