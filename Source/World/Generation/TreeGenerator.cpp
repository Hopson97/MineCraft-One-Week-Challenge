#include "TreeGenerator.h"

#include "../Chunk/Chunk.h"
#include "StructureBuilder.h"


void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    //StructureBuilder builder;

    for (int trunkY = 0; trunkY < rand.intInRange(4, 7); trunkY++)
    {
        chunk.setBlock(x, y + trunkY, z, BlockId::OakBark);
    }
}

void makeCactus(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    //StructureBuilder builder;

    for (int trunkY = 0; trunkY < rand.intInRange(4, 7); trunkY++)
    {
        chunk.setBlock(x, y + trunkY, z, BlockId::Cactus);
    }
}
