#include "Chunk.h"

#include "../../Renderer/RenderMaster.h"
#include "../../Util/Random.h"

#include <iostream>

#include "../../Maths/NoiseGenerator.h"

Chunk::Chunk(World& world, const sf::Vector2i& location)
:   m_location  (location)
,   m_pWorld    (&world)
{ }

bool Chunk::makeMesh()
{
    for (auto& chunk : m_chunks)
    {
        if (!chunk.hasMesh())
        {
            chunk.makeMesh();
            return true;
        }
    }
    return false;
}


void Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (outOfBound(x, y, z))
        return;

    int bY = y % CHUNK_SIZE;
    m_chunks.at(y / CHUNK_SIZE).setBlock(x, bY, z, block);
}

//Chunk block to SECTION BLOCK positions
ChunkBlock Chunk::getBlock(int x, int y, int z) const
{
    if (outOfBound(x, y, z))
    {
        return BlockId::Air;
    }

    int bY = y % CHUNK_SIZE;

    return m_chunks.at(y / CHUNK_SIZE).getBlock(x, bY, z);
}

bool Chunk::outOfBound(int x, int y, int z) const
{
    if (x >= CHUNK_SIZE) return true;
    if (z >= CHUNK_SIZE) return true;

    if (x < 0) return true;
    if (y < 0) return true;
    if (z < 0) return true;

    if (y >= (int)m_chunks.size() * CHUNK_SIZE)
    {
        return true;
    }

    return false;
}

void Chunk::drawChunks(RenderMaster& renderer) const
{
    for (const auto& chunk : m_chunks)
    {
        if (chunk.hasMesh())
            renderer.drawChunk(chunk.m_mesh);
    }
}

bool Chunk::hasLoaded() const
{
    return m_isLoaded;
}

void Chunk::load()
{
    static Random<std::minstd_rand> rand(500);
    NoiseGenerator temp_noiseGen(6345);
    std::array<int, CHUNK_AREA> heightMap;
    std::vector<sf::Vector3i> treelocations;

    int maxValue = 0;
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            int h = temp_noiseGen.getHeight(x, z, m_location.x, m_location.y);
            heightMap[x * CHUNK_SIZE + z] = h;

            maxValue = std::max(maxValue, h);
        }
    }

    for (int y = 0; y < maxValue / CHUNK_SIZE + 1; y++)
    {
        m_chunks.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
    }

    for (int y = 0; y < maxValue + 1; y++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        int h = heightMap[x * CHUNK_SIZE + z];

        if (y > h)
        {
            setBlock(x, y, z, BlockId::Air);
        }
        else if (y == h)
        {
            setBlock(x, y, z, BlockId::Grass);
            if (rand.intInRange(0, 100) == 10)
            {
                treelocations.emplace_back(x, y, z);
            }
        }
        else
        {
            setBlock(x, y, z, BlockId::Dirt);
        }
    }

    for (auto& tree : treelocations)
    {

    }

    m_isLoaded = true;
}

ChunkSection& Chunk::getSection(int index)
{
    while (index >= (int)m_chunks.size())
    {
        m_chunks.emplace_back(sf::Vector3i(m_location.x, m_chunks.size(), m_location.y), *m_pWorld);
    }
    return m_chunks.at(index);
}



