#include "TemperateForestBiome.h"

#include "TreeGenerator.h"

TemperateForestBiome::TemperateForestBiome(int seed) noexcept
:   Biome  (getNoiseParameters(), 55, seed)
{

}

BlockId TemperateForestBiome::getTopBlock(Rand& rand) const
{
    return rand.intInRange(0, 10) < 8 ?
        BlockId::Grass :
        BlockId::Dirt;
}

void TemperateForestBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
    makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters TemperateForestBiome::getNoiseParameters() noexcept
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 100;
    heightParams.smoothness    = 195;
    heightParams.heightOffset  = -15;
    heightParams.roughness     = 0.50;


    return heightParams;
}
