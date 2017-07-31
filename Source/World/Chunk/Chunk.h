#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <vector>
#include "ChunkSection.h"

class RenderMaster;

class Chunk : public IChunk
{
    public:
        Chunk(World& world, const sf::Vector2i& location);

        bool makeMesh();

        void setBlock       (int x, int y, int z, ChunkBlock block) override;
        ChunkBlock getBlock (int x, int y, int z) const override;

        void drawChunks (RenderMaster& renderer);

        bool hasLoaded() const;
        void load();

        ChunkSection& getSection(int index);

    private:
        void addSection();
        void addSectionsBlockTarget(int blockY);
        void addSectionsIndexTarget(int index);

        bool outOfBound(int x, int y, int z) const;

        std::vector<ChunkSection>   m_chunks;
        sf::Vector2i                m_location;

        World* m_pWorld;

        bool m_isLoaded = false;

};

#endif // CHUNK_H_INCLUDED
