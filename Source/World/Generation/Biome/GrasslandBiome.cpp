#include "GrasslandBiome.h"

#include "../Structures/TreeGenerator.h"

GrasslandBiome::GrasslandBiome(int seed)
:   Biome  (getNoiseParameters(), 1000, 20, seed)
{

}

ChunkBlock GrasslandBiome::getTopBlock(Rand& rand) const
{
    return BlockDB::get()["Grass"].id;
}

ChunkBlock GrasslandBiome::getUnderWaterBlock(Rand& rand) const
{
    return rand.intInRange(0, 10) > 8 ?
        BlockDB::get()["Dirt"].id :
        BlockDB::get()["Sand"].id;
}

ChunkBlock GrasslandBiome::getBeachBlock (Rand& rand) const
{
    return rand.intInRange(0, 10) > 2 ?
        BlockDB::get()["Dirt"].id :
        BlockDB::get()["Sand"].id;
}

void GrasslandBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
    makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters GrasslandBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves       = 9;
    heightParams.amplitude     = 85;
    heightParams.smoothness    = 235;
    heightParams.heightOffset  = -20;
    heightParams.roughness     = 0.51;

    return heightParams;
}

ChunkBlock GrasslandBiome::getPlant(Rand& rand) const
{
    return rand.intInRange(0, 10) > 6 ?
        BlockDB::get()["Rose"].id :
        BlockDB::get()["TallGrass"].id;
}
