#include "TreeGenerator.h"

#include "../Chunk/Chunk.h"
#include "StructureBuilder.h"


void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    //StructureBuilder builder;

    int h = rand.intInRange(4, 7);

    for (int trunkY = 0; trunkY < h; trunkY++)
    {
        chunk.setBlock(x, y + trunkY, z, BlockId::OakBark);
    }

    for (int lx = -2; lx < 2; lx++)
    for (int lz = -2; lz < 2; lz++)
    for (int ly =  0; ly < 3; ly++)
    {
        chunk.setBlock(lx + x, ly + h + y, lz + z, BlockId::OakLeaf);
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
