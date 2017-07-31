#include "World.h"

#include "../Renderer/RenderMaster.h"

#include <iostream>

#include "../Maths/Vector2XZ.h"

#include "../Camera.h"

namespace
{
    constexpr int temp_worldSize = 16;
    constexpr int renderDistance = 8;

    bool isOutOfBounds(const VectorXZ& chunkPos)
    {
        if (chunkPos.x < 0) return true;
        if (chunkPos.z < 0) return true;
        if (chunkPos.x >= temp_worldSize) return true;
        if (chunkPos.z >= temp_worldSize) return true;
        return false;
    }
}

World::World()
:   m_chunkManager  (*this)
{ }

//world coords into chunk column coords
ChunkBlock World::getBlock(int x, int y, int z)
{
    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

    if (isOutOfBounds(cp))
    {
        //return BlockId::Air;
    }

    return m_chunkManager.getChunk(cp.x, cp.z).getBlock(bp.x, y, bp.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (y <= 0)
        return;

    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

    if (isOutOfBounds(cp))
    {
        //return;
    }

    m_chunkManager.getChunk(cp.x, cp.z).setBlock(bp.x, y, bp.z, block);
}

//loads chunks
//make chunk meshes
void World::update(const Camera& camera)
{
    for (auto& event : m_events)
    {
        event->handle(*this);
    }

    int cX = camera.position.x / CHUNK_SIZE;
    int cZ = camera.position.z / CHUNK_SIZE;

    int minX = cX - renderDistance;
    int maxX = cX + renderDistance;

    int minZ = cZ - renderDistance;
    int maxZ = cZ + renderDistance;

    if (minZ < 0) minZ = 0;
    if (minX < 0) minX = 0;

    for (int x = minX; x < maxX; x++)
    {
        for (int z = minZ; z < maxZ; z++)
        {
            if (!m_chunkManager.chunkExistsAt(x, z))
            {
                m_chunkManager.loadChunk(x, z);
            }
            //make one mesh per frame maximum
            if (m_chunkManager.makeMesh(x, z))
                return;
        }
    }
}


void World::renderWorld(RenderMaster& renderer)
{
    renderer.drawSky();

    auto& chunkMap = m_chunkManager.getChunks();
    for (auto& chunk : chunkMap)
    {
        chunk.second.drawChunks(renderer);
    }
}

const ChunkManager& World::getChunkManager() const
{
    return m_chunkManager;
}

VectorXZ World::getBlockXZ(int x, int z)
{
    return
    {
        x % CHUNK_SIZE,
        z % CHUNK_SIZE
    };
}

VectorXZ World::getChunkXZ(int x, int z)
{
    return
    {
        x / CHUNK_SIZE,
        z / CHUNK_SIZE
    };
}
