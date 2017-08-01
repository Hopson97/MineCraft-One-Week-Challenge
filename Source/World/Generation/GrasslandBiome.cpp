#include "GrasslandBiome.h"

#include "TreeGenerator.h"

GrasslandBiome::GrasslandBiome(int seed)
:   Biome  (getNoiseParameters(), 100, seed)
{

}

BlockId GrasslandBiome::getTopBlock(Rand& rand) const
{
    return BlockId::Grass;
}

void GrasslandBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
    makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters GrasslandBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 90;
    heightParams.smoothness    = 335;
    heightParams.heightOffset  = -5;
    heightParams.roughness     = 0.50;

    return heightParams;
}
