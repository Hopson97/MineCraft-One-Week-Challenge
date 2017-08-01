#include "TerrainGenerator.h"

#include <functional>
#include <iostream>

#include "../Chunk/Chunk.h"
#include "../../Util/Random.h"


namespace
{
    int seed = 50424;
}

NoiseGenerator TerrainGenerator::m_heightNoiseGen   (seed);
NoiseGenerator TerrainGenerator::m_biomeNoiseGen    (seed * 2);

TerrainGenerator::TerrainGenerator()
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
        NoiseParameters heightParams;
        heightParams.octaves       = 7;
        heightParams.amplitude     = 70;
        heightParams.smoothness    = 235;
        heightParams.heightOffset  = -5;
        heightParams.roughness     = 0.53;

        NoiseParameters biomeParmams;
        biomeParmams.octaves       = 5;
        biomeParmams.amplitude     = 90;
        biomeParmams.smoothness    = 735;
        biomeParmams.heightOffset  = -5;
        biomeParmams.roughness     = 0.6;

        m_heightNoiseGen    .setParameters  (heightParams);
        m_biomeNoiseGen     .setParameters   (biomeParmams);
    }
}




void TerrainGenerator::generateTerrainFor(Chunk& chunk)
{
    m_pChunk = &chunk;

    auto location = chunk.getLocation();
    Random<std::minstd_rand> rand((location.x ^ location.y) << 2 );

    getHeightMap();
    getBiomeMap();
    auto maxHeight = *std::max_element(m_heightMap.begin(), m_heightMap.end());
    setBlocks(maxHeight);
}


void TerrainGenerator::getHeightMap()
{
    auto location = m_pChunk->getLocation();

    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        int h = m_heightNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
        m_heightMap[x * CHUNK_SIZE + z] = h;
    }
}

void TerrainGenerator::getBiomeMap()
{
    auto location = m_pChunk->getLocation();

    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        int h = m_biomeNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
        m_biomeMap[x * CHUNK_SIZE + z] = h;
    }
}

void TerrainGenerator::setBlocks(int maxHeight)
{
    for (int y = 0; y < maxHeight + 1; y++)
    for (int x = 0; x < CHUNK_SIZE; x++)
    for (int z = 0; z < CHUNK_SIZE; z++)
    {
        int height = m_heightMap[x * CHUNK_SIZE + z];
        int biome  = m_biomeMap [x * CHUNK_SIZE + z];

        if (y > height)
        {
            continue;
        }
        else if (y == height)
        {
            //if (y > WATER_LEVEL)
            {
                setTopBlock(x, y, z);
            }/*
            else
            {
                m_pChunk->setBlock(x, y, z, BlockId::Grass);
            }*/

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
}

void TerrainGenerator::setTopBlock(int x, int y, int z)
{
    int biome = m_biomeMap [x * CHUNK_SIZE + z];

    if (biome < 100)
    {
        m_pChunk->setBlock(x, y, z, BlockId::Grass);
    }
    else
    {
        m_pChunk->setBlock(x, y, z, BlockId::Sand);
    }
}

