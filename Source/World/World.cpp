#include "World.h"

#include "../Renderer/RenderMaster.h"

#include <iostream>

namespace
{
    constexpr int temp_worldSize = 8;

    struct VectorXZ
    {
        int x, z;
    };

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
{
    for (int x = 0; x < temp_worldSize; x++)
    {
        for (int z = 0; z < temp_worldSize; z++)
        {
            addChunk(x, z);
        }
    }

    for (auto& chunk : m_chunks)
    {
        chunk.makeMesh();
    }
}

//world coords into chunk column coords
ChunkBlock World::getBlock(int x, int y, int z) const
{
    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

    if (isOutOfBounds(cp))
    {
        return BlockId::Air;
    }

    return m_chunks.at(cp.x * temp_worldSize + cp.z).getBlock(bp.x, y, bp.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

    if (isOutOfBounds(cp))
    {
        return;
    }

    m_chunks.at(cp.x * temp_worldSize + cp.z).setBlock(bp.x, y, bp.z, block);
}

void World::editBlock(int x, int y, int z, ChunkBlock block)
{
    auto cp = getChunkXZ(x, z);

    if (isOutOfBounds(cp))
    {
        return;
    }

    setBlock(x, y, z, block);
    m_changedChunks.push_back(&m_chunks.at(cp.x * temp_worldSize + cp.z));
}

void World::renderWorld(RenderMaster& renderer)
{
    for (auto& chunk : m_changedChunks)
    {
        chunk->makeMesh();
    }
    m_changedChunks.clear();

    for (auto& chunk : m_chunks)
        chunk.drawChunks(renderer);
}

void World::addChunk(int x, int z)
{
    m_chunks.emplace_back(*this, sf::Vector2i(x, z));
}

