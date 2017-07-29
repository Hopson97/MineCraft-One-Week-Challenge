#include "Chunk.h"

#include "../../Renderer/RenderMaster.h"
#include "ChunkMeshBuilder.h"
#include "../../Util/Random.h"

#include <iostream>

Chunk::Chunk(World& world, const sf::Vector2i& location)
:   m_location  (location)
,   m_pWorld    (&world)
{
    for (int y = 0; y < 3; y++)
    {
        m_chunks.emplace_back(sf::Vector3i(location.x, y, location.y), world);
    }

    int h =  m_chunks.size() * CHUNK_SIZE - 1;
    for (int y = 0; y < (int)m_chunks.size() * CHUNK_SIZE; y++)
    for (int x = 0; x < 16; x++)
    for (int z = 0; z < 16; z++)
    {
        if (y == h)
        {
            setBlock(x, y, z, BlockId::Grass);
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
}

bool Chunk::makeMesh()
{
    for (auto& chunk : m_chunks)
    {
        if (!chunk.hasMesh())
        {
            ChunkMeshBuilder(chunk, chunk.m_mesh).buildMesh();
            chunk.m_mesh.bufferMesh();
            chunk.m_hasMesh = true;
        }
    }
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

void Chunk::drawChunks(RenderMaster& renderer)
{
    for (auto& chunk : m_chunks)
    {
        if (chunk.hasMesh())
            renderer.drawChunk(chunk.m_mesh);
    }
}

