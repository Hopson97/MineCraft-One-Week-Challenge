#include "ChunkSection.h"

#include "../Block/BlockId.h"

#include "../World.h"
#include "ChunkMeshBuilder.h"

#include <fstream>
#include <iostream>
#include <thread>

ChunkSection::ChunkSection(const sf::Vector3i &location, World &world)
    : m_aabb({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE})
    , m_location(location)
    , m_pWorld(&world)
{
    m_aabb.update({location.x * CHUNK_SIZE, location.y * CHUNK_SIZE,
                   location.z * CHUNK_SIZE});
}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z)) {
        auto location = toWorldPosition(x, y, z);
        m_pWorld->setBlock(location.x, location.y, location.z, block);
        return;
    }

    m_layers[y].update(block);

    m_blocks[getIndex(x, y, z)] = block;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const
{
    if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z)) {
        auto location = toWorldPosition(x, y, z);
        return m_pWorld->getBlock(location.x, location.y, location.z);
    }

    return m_blocks[getIndex(x, y, z)];
}

const sf::Vector3i ChunkSection::getLocation() const
{
    return m_location;
}

bool ChunkSection::hasMesh() const
{
    return m_hasMesh;
}

bool ChunkSection::hasBuffered() const
{
    return m_hasBufferedMesh;
}

sf::Vector3i ChunkSection::toWorldPosition(int x, int y, int z) const
{
    return {m_location.x * CHUNK_SIZE + x, m_location.y * CHUNK_SIZE + y,
            m_location.z * CHUNK_SIZE + z};
}

void ChunkSection::makeMesh()
{
    ChunkMeshBuilder(*this, m_meshes).buildMesh();
    m_hasMesh = true;
    m_hasBufferedMesh = false;
}

void ChunkSection::bufferMesh()
{
    m_meshes.solidMesh.bufferMesh();
    m_meshes.waterMesh.bufferMesh();
    m_meshes.floraMesh.bufferMesh();
    m_hasBufferedMesh = true;
}

const ChunkSection::Layer &ChunkSection::getLayer(int y) const
{
    if (y == -1) {
        return m_pWorld->getChunkManager()
            .getChunk(m_location.x, m_location.z)
            .getSection(m_location.y - 1)
            .getLayer(CHUNK_SIZE - 1);
    }
    else if (y == CHUNK_SIZE) {
        return m_pWorld->getChunkManager()
            .getChunk(m_location.x, m_location.z)
            .getSection(m_location.y + 1)
            .getLayer(0);
    }
    else {
        return m_layers[y];
    }
}

void ChunkSection::deleteMeshes()
{
    if (m_hasMesh) {
        m_hasBufferedMesh = false;
        m_hasMesh = false;
        m_meshes.solidMesh.deleteData();
        m_meshes.waterMesh.deleteData();
        m_meshes.floraMesh.deleteData();
    }
}

ChunkSection &ChunkSection::getAdjacent(int dx, int dz)
{
    int newX = m_location.x + dx;
    int newZ = m_location.z + dz;

    return m_pWorld->getChunkManager()
        .getChunk(newX, newZ)
        .getSection(m_location.y);
}

bool ChunkSection::outOfBounds(int value)
{
    return value >= CHUNK_SIZE || value < 0;
}

int ChunkSection::getIndex(int x, int y, int z)
{
    return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
