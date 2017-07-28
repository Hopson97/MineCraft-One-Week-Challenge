#include "ChunkSection.h"

#include "../Block/BlockId.h"

ChunkSection::ChunkSection()
{
    m_location = {0, 0, 0};
}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (outOfBounds(x)) return;
    if (outOfBounds(y)) return;
    if (outOfBounds(z)) return;

    m_blocks[getIndex(x, y, z)] = block;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const
{
    if (outOfBounds(x)) return BlockId::Air;
    if (outOfBounds(y)) return BlockId::Air;;
    if (outOfBounds(z)) return BlockId::Air;;

    return m_blocks[getIndex(x, y, z)];
}

const sf::Vector3i ChunkSection::getLocation() const
{
    return m_location;
}

bool ChunkSection::outOfBounds(int value)
{
    return  value >= CHUNK_SIZE ||
            value < 0;
}

int ChunkSection::getIndex(int x, int y, int z)
{
    return  y *
            CHUNK_AREA + z *
            CHUNK_SIZE + x;
}
