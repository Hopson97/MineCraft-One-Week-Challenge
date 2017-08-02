#include "TerrainGenerator.h"

#include <functional>
#include <iostream>

#include "../Chunk/Chunk.h"
#include "../../Util/Random.h"

#include "TreeGenerator.h"

#include "../../Maths/GeneralMaths.h"

namespace
{
    int seed = RandomSingleton::get().intInRange(424, 325322);
}

NoiseGenerator TerrainGenerator::m_biomeNoiseGen    (seed * 2);

TerrainGenerator::TerrainGenerator()
:   m_grassBiome    (seed)
,   m_lightForest   (seed)
,   m_desertBiome   (seed)
,   m_oceanBiome    (seed)
{
    setUpNoise();
}

void TerrainGenerator::setUpNoise()
{
    static bool noiseGen = false;
    if (!noiseGen)
    {
        std::cout << "making noise\n";
        noiseGen = true;

        NoiseParameters biomeParmams;
        biomeParmams.octaves       = 5;
        biomeParmams.amplitude     = 125;
        biomeParmams.smoothness    = 1035;
        biomeParmams.heightOffset  = 0;
        biomeParmams.roughness     = 0.7;

        m_biomeNoiseGen     .setParameters   (biomeParmams);
    }
}

void TerrainGenerator::generateTerrainFor(Chunk& chunk)
{
    m_pChunk = &chunk;

    auto location = chunk.getLocation();
    m_random.setSeed((location.x ^ location.y) << 2 );

    getBiomeMap();
    getHeightMap();

    auto maxHeight = m_heightMap.getMaxValue();

    maxHeight = std::max(maxHeight, WATER_LEVEL);
    setBlocks(maxHeight);
}

void TerrainGenerator::getHeightIn (int xMin, int zMin, int xMax, int zMax)
{

    auto getHeightAt = [&](int x, int z)
    {
        const Biome& biome = getBiome(x, z);

        return biome.getHeight(x, z,
                               m_pChunk->getLocation().x,
                               m_pChunk->getLocation().y);
    };

    int bottomLeft  = getHeightAt(xMin, zMin);
    int bottomRight = getHeightAt(xMax, zMin);
    int topLeft     = getHeightAt(xMin, zMax);
    int topRight    = getHeightAt(xMax, zMax);

    for (int x = xMin; x < xMax; ++x)
    for (int z = zMin; z < zMax; ++z)
    {
        if (x == CHUNK_SIZE)
            continue;
        if (z == CHUNK_SIZE)
            continue;

        int h = bilinearInterpolation(bottomLeft, topLeft, bottomRight, topRight,
                                      xMin, xMax,
                                      zMin, zMax,
                                      x, z);

        m_heightMap.get(x, z) = h;
    }
}



void TerrainGenerator::getHeightMap()
{
    constexpr static auto HALF_CHUNK    = CHUNK_SIZE / 2;
    constexpr static auto CHUNK         = CHUNK_SIZE;

    getHeightIn(0,          0,          HALF_CHUNK,     HALF_CHUNK);
    getHeightIn(HALF_CHUNK, 0,          CHUNK,          HALF_CHUNK);
    getHeightIn(0,          HALF_CHUNK, HALF_CHUNK,     CHUNK);
    getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK,          CHUNK);
}

void TerrainGenerator::getBiomeMap()
{
    auto location = m_pChunk->getLocation();

    for (int x = 0; x < CHUNK_SIZE + 1; x++)
    for (int z = 0; z < CHUNK_SIZE + 1; z++)
    {
        int h = m_biomeNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
        m_biomeMap.get(x, z) = h;
    }
}

void TerrainGenerator::setBlocks(int maxHeight)
{
    std::vector<sf::Vector3i> trees;

    for (int y = 0; y < maxHeight + 1; y++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        int height = m_heightMap.get(x, z);
        auto& biome = getBiome(x, z);

        if (y > height)
        {
            if (y <= WATER_LEVEL)
            {
                m_pChunk->setBlock(x, y, z, BlockId::Water);
            }
            continue;
        }
        else if (y == height)
        {
            if (y >= WATER_LEVEL)
            {
                if (m_random.intInRange(0, biome.getTreeFrequency()) == 5 )
                {
                    trees.emplace_back(x, y, z);
                }
                setTopBlock(x, y, z);
            }
            else
            {
                m_pChunk->setBlock(x, y, z, m_random.intInRange(0, 10) < 5 ?
                                                BlockId::Sand :
                                                BlockId::Dirt);
            }

        }
        else if (y > height - 3)
        {
            m_pChunk->setBlock(x, y, z, BlockId::Dirt);
        }
        else
        {
            m_pChunk->setBlock(x, y, z, BlockId::Stone);
        }
    }

    for (auto& tree : trees)
    {
        int x = tree.x;
        int z = tree.z;

        getBiome(x, z).makeTree(m_random, *m_pChunk, x, tree.y, z);
    }
}

void TerrainGenerator::setTopBlock(int x, int y, int z)
{
    m_pChunk->setBlock(x, y, z, getBiome(x, z).getTopBlock(m_random));

}

const Biome& TerrainGenerator::getBiome(int x, int z) const
{
    int biomeValue = m_biomeMap.get(x, z);

    if (biomeValue > 155)
    {
        return m_desertBiome;
    }
    else if (biomeValue > 115)
    {
        return m_lightForest;
    }
    else if (biomeValue > 100)
    {
        return m_grassBiome;
    }
    else
    {
        return m_oceanBiome;
    }
}
