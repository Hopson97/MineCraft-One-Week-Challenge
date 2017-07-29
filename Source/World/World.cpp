#include "World.h"

#include "../Renderer/RenderMaster.h"

World::World()
:   m_chunk (*this)
{

}

ChunkBlock World::getBlock(int x, int y, int z) const
{
    int bX = x % CHUNK_SIZE;
    int bY = y % CHUNK_SIZE;
    int bZ = z % CHUNK_SIZE;

    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    return m_chunk.getBlock(bX, bY, bZ);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{

}

void World::renderWorld(RenderMaster& renderer)
{
    m_chunk.drawChunks(renderer);
}

