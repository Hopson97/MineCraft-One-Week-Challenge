#include "World.h"

#include "../Renderer/RenderMaster.h"

#include <iostream>

#include "../Maths/Vector2XZ.h"

namespace
{
    constexpr int temp_worldSize = 8;

    VectorXZ getBlockXZ(int x, int z)
    {
        return
        {
            x % CHUNK_SIZE,
            z % CHUNK_SIZE
        };
    }

    VectorXZ getChunkXZ(int x, int z)
    {
        return
        {
            x / CHUNK_SIZE,
            z / CHUNK_SIZE
        };
    }

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
:   m_chunkManager(*this)
{
    for (int x = 0; x < temp_worldSize; x++)
    {
        for (int z = 0; z < temp_worldSize; z++)
        {
            m_chunkManager.getChunk(x, z).load();
        }
    }

    for (int x = 0; x < temp_worldSize; x++)
    {
        for (int z = 0; z < temp_worldSize; z++)
        {
            m_chunkManager.makeMesh(x, z);
        }
    }
}

//world coords into chunk column coords
ChunkBlock World::getBlock(int x, int y, int z)
{
    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

    if (isOutOfBounds(cp))
    {
        return BlockId::Air;
    }

    return m_chunkManager.getChunk(cp.x, cp.z).getBlock(bp.x, y, bp.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (y == 0)
        return;

    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

    if (isOutOfBounds(cp))
    {
        return;
    }

    auto& chunk = m_chunkManager.getChunk(cp.x, cp.z);
    chunk.setBlock(bp.x, y, bp.z, block);
    if (chunk.hasLoaded())
    {
        m_rebuildChunks.emplace(cp.x, y / CHUNK_SIZE, cp.z);
    }
}

void World::renderWorld(RenderMaster& renderer)
{
    for (auto& location : m_rebuildChunks)
    {
        ChunkSection& section = m_chunkManager.getChunk(location.x, location.z).getSection(location.y);
        section.makeMesh();
    }
    m_rebuildChunks.clear();


    renderer.drawSky();

    const auto& chunkMap = m_chunkManager.getChunks();
    for (auto& chunk : chunkMap)
    {
        chunk.second.drawChunks(renderer);
    }
}

