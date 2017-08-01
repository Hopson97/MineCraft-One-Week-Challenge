#include "DesertBiome.h"

#include "TreeGenerator.h"

DesertBiome::DesertBiome(int seed)
:   Biome  (getNoiseParameters(), 175, seed)
{

}

BlockId DesertBiome::getTopBlock(Rand& rand) const
{
    return BlockId::Sand;
}

void DesertBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
    makeCactus(chunk, rand, x, y, z);
}

NoiseParameters DesertBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 80;
    heightParams.smoothness    = 335;
    heightParams.heightOffset  = 0;
    heightParams.roughness     = 0.53;


    return heightParams;
}
