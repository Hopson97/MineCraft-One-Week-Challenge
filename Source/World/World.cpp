#include "World.h"

#include "../Renderer/RenderMaster.h"

#include <iostream>

World::World()
{
    for (int x = 0; x < 16; x++)
    {
        for (int z = 0; z < 16; z++)
        {
            m_chunks.emplace_back(*this, sf::Vector2i(x, z));
        }
    }

    for (auto& chunk : m_chunks)
        chunk.makeAllMeshtemp();
}

//world coords into chunk column coords
ChunkBlock World::getBlock(int x, int y, int z) const
{
    int bX = x % CHUNK_SIZE;
    int bZ = z % CHUNK_SIZE;

    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    if (cX < 0) return BlockId::Air;
    if (cZ < 0) return BlockId::Air;
    if (cX >= 16) return BlockId::Air;
    if (cZ >= 16) return BlockId::Air;

    return m_chunks.at(cX * 16 + cZ).getBlock(bX, y, bZ);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{

}

void World::renderWorld(RenderMaster& renderer)
{
    for (auto& chunk : m_chunks)
        chunk.drawChunks(renderer);
}

