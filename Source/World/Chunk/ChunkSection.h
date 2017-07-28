#ifndef CHUNKSECTION_H_INCLUDED
#define CHUNKSECTION_H_INCLUDED

#include <array>
#include <SFML/Graphics.hpp>

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"

class ChunkSection
{
    public:
        ChunkSection();

        void setBlock       (int x, int y, int z, ChunkBlock block);
        ChunkBlock getBlock (int x, int y, int z) const;

        const sf::Vector3i getLocation() const;

    private:
        static bool outOfBounds (int value);
        static int  getIndex    (int x, int y, int z);

        std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;

        sf::Vector3i m_location;
};

#endif // CHUNKSECTION_H_INCLUDED
