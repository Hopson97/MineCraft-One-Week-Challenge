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
    addSectionsBlockTarget(y);
    if (outOfBound(x, y, z))
        return;

    int bY = y % CHUNK_SIZE;
    m_chunks[y / CHUNK_SIZE].setBlock(x, bY, z, block);
}

//Chunk block to SECTION BLOCK positions
ChunkBlock Chunk::getBlock(int x, int y, int z) const
{
    if (outOfBound(x, y, z))
    {
        return BlockId::Air;
    }

    int bY = y % CHUNK_SIZE;

    return m_chunks[y / CHUNK_SIZE].getBlock(x, bY, z);
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

void Chunk::drawChunks(RenderMaster& renderer)
{
    for (auto& chunk : m_chunks)
    {
        if (chunk.hasMesh())
        {
            if (!chunk.hasBuffered())
            {
                chunk.bufferMesh();
            }
            renderer.drawChunk(chunk.m_mesh);
        }
    }
}

bool Chunk::hasLoaded() const
{
    return m_isLoaded;
}

void Chunk::load()
{
    static int seed = RandomSingleton::get().intInRange(444,444444);
    if (hasLoaded())
        return;

    Random<std::minstd_rand> rand((m_location.x ^ m_location.y) << 2 );

    NoiseGenerator temp_noiseGen(seed);
    std::array<int, CHUNK_AREA> heightMap;
    std::vector<sf::Vector3i> treelocations;

    int maxValue = 0;
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            int h = temp_noiseGen.getHeight(x, z, m_location.x + 10, m_location.y + 10);
            heightMap[x * CHUNK_SIZE + z] = h;

            maxValue = std::max(maxValue, h);
        }
    }

    for (int y = 0; y < maxValue + 1; y++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        int h = heightMap[x * CHUNK_SIZE + z];

        if (y > h)
        {
            continue;
        }
        else if (y == h)
        {
            if (y > WATER_LEVEL)
            {
                setBlock(x, y, z, BlockId::Grass);
                if (rand.intInRange(0, 150) == 0)
                {
                    treelocations.emplace_back(x, y, z);
                }
            }
            else
            {
                setBlock(x, y, z, BlockId::Grass);
            }

        }
        else if (y > h - 3)
        {
            setBlock(x, y, z, BlockId::Dirt);
        }
        else
        {
            setBlock(x, y, z, BlockId::Stone);
        }
    }

    for (auto& tree : treelocations)
    {
        int h = rand.intInRange(5, 9);
        for (int y = 0; y < h; y++)
        {
            setBlock(tree.x, tree.y + y, tree.z, BlockId::OakBark);
        }
        for (int x = -2; x < 2; x++)
        for (int z = -2; z < 2; z++)
        for (int y =  0; y < 3; y++)
        {
            setBlock(tree.x + x, tree.y + h + y, tree.z + z, BlockId::OakLeaf);
        }

    }

    m_isLoaded = true;
}

ChunkSection& Chunk::getSection(int index)
{
    static ChunkSection errorSection({444,444,444}, *m_pWorld);

    if (index >= m_chunks.size() || index < 0) return errorSection;

    return m_chunks[index];
}

void Chunk::addSection()
{
    int y = m_chunks.size();
    m_chunks.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
}

void Chunk::addSectionsBlockTarget(int blockY)
{
    int index = blockY / CHUNK_SIZE;
    addSectionsIndexTarget(index);
}

void Chunk::addSectionsIndexTarget(int index)
{
    while ((int)m_chunks.size() < index + 1)
    {
        addSection();
    }
}



