#include "OceanBiome.h"

#include "../Structures/TreeGenerator.h"

OceanBiome::OceanBiome(int seed)
:   Biome  (getNoiseParameters(), 50, 100, seed)
{

}

ChunkBlock OceanBiome::getTopBlock(Rand& rand) const
{
    return BlockDB::get()["Grass"].id;
}

ChunkBlock OceanBiome::getUnderWaterBlock(Rand& rand) const
{
    return BlockDB::get()["Sand"].id;
}

void OceanBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
    rand.intInRange(0, 5) < 3 ?
        makePalmTree(chunk, rand, x, y, z) :
        makeOakTree (chunk, rand, x, y, z);
}

NoiseParameters OceanBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves       = 7;
    heightParams.amplitude     = 43;
    heightParams.smoothness    = 55;
    heightParams.heightOffset  = 0;
    heightParams.roughness     = 0.50;

    return heightParams;
}

ChunkBlock OceanBiome::getPlant(Rand& rand) const
{
    return rand.intInRange(0, 10) > 6 ?
        BlockDB::get()["Rose"].id :
        BlockDB::get()["TallGrass"].id;
}
