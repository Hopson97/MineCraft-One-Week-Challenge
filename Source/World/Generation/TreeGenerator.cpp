#include "TreeGenerator.h"

#include "../Chunk/Chunk.h"
#include "StructureBuilder.h"


void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    StructureBuilder builder;

    int h = rand.intInRange(4, 7);
    int leafSize = 2;

    int newY = h + y;
    builder.fill(newY,      x - leafSize, x + leafSize, z - leafSize, z + leafSize, BlockId::OakLeaf);
    builder.fill(newY - 1,  x - leafSize, x + leafSize, z - leafSize, z + leafSize, BlockId::OakLeaf);

    for (int32_t zLeaf = -leafSize + 1; zLeaf <= leafSize - 1; zLeaf++)
    {
        builder.addBlock(x, newY + 1, z + zLeaf, BlockId::OakLeaf);
    }

    for (int32_t xLeaf = -leafSize + 1; xLeaf <= leafSize - 1; xLeaf++)
    {
        builder.addBlock(x + xLeaf, newY + 1, z, BlockId::OakLeaf);
    }

    builder.makeColumn(x, z, y, h, BlockId::OakBark);
    builder.build(chunk);
}

void makePalmTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    StructureBuilder builder;

    int height = rand.intInRange(7, 9);
    int diameter = rand.intInRange(4, 6);

    for (int xLeaf = -diameter; xLeaf < diameter; xLeaf++)
    {
        builder.addBlock(xLeaf + x, y + height, z, BlockId::OakLeaf);
    }
    for (int zLeaf = -diameter; zLeaf < diameter; zLeaf++)
    {
        builder.addBlock(x, y + height, zLeaf + z, BlockId::OakLeaf);
    }

    builder.addBlock(x,             y + height - 1, z + diameter,   BlockId::OakLeaf);
    builder.addBlock(x,             y + height - 1, z - diameter,   BlockId::OakLeaf);
    builder.addBlock(x + diameter,  y + height - 1, z,              BlockId::OakLeaf);
    builder.addBlock(x - diameter,  y + height - 1, z,              BlockId::OakLeaf);
    builder.addBlock(x,             y + height + 1, z,              BlockId::OakLeaf);

    builder.makeColumn(x, z, y, height, BlockId::OakBark);
    builder.build(chunk);
}


void makeCactus(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    StructureBuilder builder;
    builder.makeColumn(x, z, y, rand.intInRange(4, 7), BlockId::Cactus);
    builder.build(chunk);
}
