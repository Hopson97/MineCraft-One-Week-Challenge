#include "ChunkManager.h"

ChunkManager::ChunkManager(World& world)
:   m_world (&world)
{

}

Chunk& ChunkManager::getChunk(int x, int z)
{
    if (m_chunks.find({x, z}) == m_chunks.end())
    {
        VectorXZ    key     {x, z};
        Chunk       chunk   {*m_world, {x, z}};
        m_chunks.emplace(key, std::move(chunk));
    }

    return m_chunks.at({x, z});
}

const std::unordered_map<VectorXZ, Chunk>& ChunkManager::getChunks() const
{
    return m_chunks;
}

bool ChunkManager::makeMesh(int x, int z)
{
    return getChunk(x, z).makeMesh();
}

