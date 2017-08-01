#include "Biome.h"

#include "TreeGenerator.h"

/**
    GRASS LAND
*/
GrasslandBiome::GrasslandBiome(int seed)
:   m_heightGenerator   (seed)
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 80;
    heightParams.smoothness    = 335;
    heightParams.heightOffset  = -5;
    heightParams.roughness     = 0.56;

    m_heightGenerator.setParameters(heightParams);
}

BlockId GrasslandBiome::getTopBlock(Rand& rand)
{
    return BlockId::Grass;
}

void GrasslandBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z)
{
    makeOakTree(chunk, rand, x, y, z);
}

int GrasslandBiome::getHeight(int x, int z, int chunkX, int chunkZ)
{
    return m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int GrasslandBiome::getTreeFrequency()
{
    return 100;
}

/**
    LIGHT FOREST
*/
LightForestBiome::LightForestBiome(int seed)
:   m_heightGenerator   (seed)
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 120;
    heightParams.smoothness    = 135;
    heightParams.heightOffset  = -15;
    heightParams.roughness     = 0.52;

    m_heightGenerator.setParameters(heightParams);
}

BlockId LightForestBiome::getTopBlock(Rand& rand)
{
    return rand.intInRange(0, 10) > 8 ?
        BlockId::Grass :
        BlockId::Dirt;
}

void LightForestBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z)
{
    makeOakTree(chunk, rand, x, y, z);
}

int LightForestBiome::getHeight(int x, int z, int chunkX, int chunkZ)
{
    return m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int LightForestBiome::getTreeFrequency()
{
    return 50;
}

/**
    DESERT
*/
DesertBiome::DesertBiome(int seed)
:   m_heightGenerator   (seed)
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 70;
    heightParams.smoothness    = 335;
    heightParams.heightOffset  = 0;
    heightParams.roughness     = 0.53;

    m_heightGenerator.setParameters(heightParams);
}

BlockId DesertBiome::getTopBlock(Rand& rand)
{
    return BlockId::Sand;
}

void DesertBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z)
{
    makeCactus(chunk, rand, x, y, z);
}

int DesertBiome::getHeight(int x, int z, int chunkX, int chunkZ)
{
    return m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int DesertBiome::getTreeFrequency()
{
    return 200;
}
