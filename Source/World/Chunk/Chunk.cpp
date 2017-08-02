#include "Chunk.h"

#include "../../Renderer/RenderMaster.h"
#include "../../Util/Random.h"
#include "../../Maths/NoiseGenerator.h"
#include "../../Camera.h"
#include "../Generation/TerrainGenerator.h"

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

void Chunk::drawChunks(RenderMaster& renderer, const Camera& camera)
{
    for (auto& chunk : m_chunks)
    {
        if (chunk.hasMesh())
        {
            if (!chunk.hasBuffered())
            {
                chunk.bufferMesh();
            }

            if (camera.getFrustum().isBoxInFrustum(chunk.m_aabb))
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
    if (hasLoaded())
        return;

    TerrainGenerator gen;
    gen.generateTerrainFor(*this);
    m_isLoaded = true;
}

ChunkSection& Chunk::getSection(int index)
{
    static ChunkSection errorSection({444,444,444}, *m_pWorld);

    if (index >= (int)m_chunks.size() || index < 0)
        return errorSection;

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
