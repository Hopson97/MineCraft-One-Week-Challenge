#include "TemperateForestBiome.h"

#include "../Structures/TreeGenerator.h"

TemperateForestBiome::TemperateForestBiome(int seed)
:   Biome  (getNoiseParameters(), 0, 0, seed)
{

}

ChunkBlock TemperateForestBiome::getTopBlock(Rand& rand) const
{
    return rand.intInRange(0, 10) < 8 ?
        BlockId::Grass :
        BlockId::Dirt;
}

ChunkBlock TemperateForestBiome::getUnderWaterBlock(Rand& rand) const
{
    return rand.intInRange(0, 10) > 8 ?
        BlockId::Dirt :
        BlockId::Sand;
}

void TemperateForestBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
    makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters TemperateForestBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves       = 6;
    heightParams.amplitude     = 64;
    heightParams.smoothness    = 225;
    heightParams.heightOffset  = -15;
    heightParams.roughness     = 0.48;

    return heightParams;
}

ChunkBlock TemperateForestBiome::getPlant(Rand& rand) const
{
    return BlockId::TallGrass;
}
