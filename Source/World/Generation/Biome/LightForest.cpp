#include "LightForest.h"

#include "../Structures/TreeGenerator.h"

LightForest::LightForest(int seed)
:   Biome  (getNoiseParameters(), 100, 50, seed)
{

}

ChunkBlock LightForest::getTopBlock(Rand& rand) const
{
    return BlockId::Grass;
}

ChunkBlock LightForest::getUnderWaterBlock(Rand& rand) const
{
    return rand.intInRange(0, 10) > 9 ?
        BlockId::Sand :
        BlockId::Dirt;
}

void LightForest::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
    makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters LightForest::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 85;
    heightParams.smoothness    = 235;
    heightParams.heightOffset  = -20;
    heightParams.roughness     = 0.51;

    return heightParams;
}

ChunkBlock LightForest::getPlant(Rand& rand) const
{
    return rand.intInRange(0, 10) > 6 ?
        BlockId::Rose :
        BlockId::TallGrass;
}
