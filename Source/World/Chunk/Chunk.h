#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

#include <vector>
#include "ChunkSection.h"
#include "../../Util/NonCopyable.h"

class RenderMaster;
class Camera;

class Chunk : public IChunk
{
    public:
        Chunk() = default;
        Chunk(World& world, const sf::Vector2i& location);

        bool makeMesh();

        void setBlock       (int x, int y, int z, ChunkBlock block) override;
        ChunkBlock getBlock (int x, int y, int z) const override;

        void drawChunks (RenderMaster& renderer, const Camera& camera);

        bool hasLoaded() const noexcept;
        void load();

        ChunkSection& getSection(int index);

        const sf::Vector2i& getLocation() const noexcept { return m_location; }

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
