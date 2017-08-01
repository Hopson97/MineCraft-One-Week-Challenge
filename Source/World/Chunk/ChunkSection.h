#ifndef CHUNKSECTION_H_INCLUDED
#define CHUNKSECTION_H_INCLUDED

#include <array>
#include <SFML/Graphics.hpp>

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"
#include "ChunkMesh.h"
#include "IChunk.h"

#include "../../Physics/AABB.h"

class World;

class ChunkSection : public IChunk
{
    friend class Chunk;

    class Layer
    {
        public:
            void update(ChunkBlock c)
            {
                if (c == 0)
                {
                    m_solidBlockCount--;
                }
                else
                {
                    m_solidBlockCount++;
                }
            }

            bool isAllSolid() const
            {
                return m_solidBlockCount == CHUNK_AREA;
            }

        private:
            int m_solidBlockCount = 0;
    };

    public:
        ChunkSection(const sf::Vector3i& position, World& world);

        void setBlock       (int x, int y, int z, ChunkBlock block) override;
        ChunkBlock getBlock (int x, int y, int z) const override;

        const sf::Vector3i getLocation() const noexcept;

        bool hasMesh    () const noexcept;
        bool hasBuffered() const noexcept;

        void makeMesh();
        void bufferMesh();

        const Layer& getLayer (int y) const;
        ChunkSection& getAdjacent(int dx, int dz);

    private:
        sf::Vector3i toWorldPosition (int x, int y, int z) const;

        static bool outOfBounds (int value);
        static int  getIndex    (int x, int y, int z);

        std::array<ChunkBlock, CHUNK_VOLUME>    m_blocks;
        std::array<Layer, CHUNK_SIZE>           m_layers;

        ChunkMesh       m_mesh;
        AABB            m_aabb;
        sf::Vector3i    m_location;

        World* m_pWorld;

        bool m_hasMesh = false;
        bool m_hasBufferedMesh = false;
};

#endif // CHUNKSECTION_H_INCLUDED
