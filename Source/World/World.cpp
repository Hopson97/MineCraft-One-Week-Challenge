#include "World.h"

#include "../Renderer/RenderMaster.h"

#include <iostream>

#include "../Maths/Vector2XZ.h"

#include "../Camera.h"

namespace
{
    constexpr int renderDistance = 20;
    constexpr float GRAV = -3;
}

World::World()
:   m_chunkManager  (*this)
{ }

//world coords into chunk column coords
ChunkBlock World::getBlock(int x, int y, int z)
{
    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

    return m_chunkManager.getChunk(cp.x, cp.z).getBlock(bp.x, y, bp.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (y <= 0)
        return;

    auto bp = getBlockXZ(x, z);
    auto cp = getChunkXZ(x, z);

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
    m_events.clear();

    updateChunks();

    for (int x = 0; x < renderDistance; x++)
    {
        for (int z = 0; z < renderDistance; z++)
        {
            if (m_chunkManager.makeMesh(x, z))
                return;
        }
    }
}

void World::updateChunk(int blockX, int blockY, int blockZ)
{
    std::cout << "Update chunk" << " X: " << blockX
                                << " Y: " << blockY
                                << " Z: " << blockZ << "\n\n";

    auto addChunkToUpdateBatch = [&](const sf::Vector3i& key, ChunkSection& section)
    {
        m_chunkUpdates.emplace(key, &section);
    };

    auto cp = getChunkXZ(blockX, blockZ);
    auto cy        = blockY / CHUNK_SIZE;

    sf::Vector3i key(cp.x, cy, cp.z);
    addChunkToUpdateBatch(key, m_chunkManager.getChunk(cp.x, cp.z).getSection(cy));

    auto sectionBlockXZ = getBlockXZ(blockX, blockZ);
    auto sectionBlockY  = blockY % CHUNK_SIZE;

    if (sectionBlockXZ.x == 0)
    {
        sf::Vector3i newKey(cp.x - 1, cy, cp.z);
        addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }
    else if (sectionBlockXZ.x == CHUNK_SIZE - 1)
    {
        sf::Vector3i newKey(cp.x + 1, cy, cp.z);
        addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }

    if (sectionBlockY == 0)
    {
        sf::Vector3i newKey(cp.x, cy - 1, cp.z);
        addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }
    else if (sectionBlockY == CHUNK_SIZE - 1)
    {
        sf::Vector3i newKey(cp.x, cy + 1, cp.z);
        addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }

    if (sectionBlockXZ.z == 0)
    {
        sf::Vector3i newKey(cp.x, cy, cp.z - 1);
        addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }
    else if (sectionBlockXZ.z == CHUNK_SIZE - 1)
    {
        sf::Vector3i newKey(cp.x, cy, cp.z + 1);
        addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
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

void World::updateChunks()
{
    for (auto& c : m_chunkUpdates)
    {
        std::cout << m_chunkUpdates.size() << "\n";
        ChunkSection& s = *c.second;
        s.makeMesh();
    }
    m_chunkUpdates.clear();
}

