#include "World.h"

#include "../Renderer/RenderMaster.h"

#include <iostream>

World::World()
:   m_chunk (*this)
{

}

//world coords into chunk column coords
ChunkBlock World::getBlock(int x, int y, int z) const
{
    int bX = x % CHUNK_SIZE;
    int bY = y;
    int bZ = z % CHUNK_SIZE;

    int cX = x / CHUNK_SIZE;
    int cZ = z / CHUNK_SIZE;

    return m_chunk.getBlock(bX, y, bZ);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{

}

void World::renderWorld(RenderMaster& renderer)
{
    m_chunk.drawChunks(renderer);
}

