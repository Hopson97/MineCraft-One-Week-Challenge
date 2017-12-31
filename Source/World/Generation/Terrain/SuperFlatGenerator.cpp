#include "SuperFlatGenerator.h"

#include <iostream>

#include "../../Chunk/Chunk.h"
#include "../../WorldConstants.h"

void SuperFlatGenerator::generateTerrainFor(Chunk& chunk)
{
    ChunkBlock dirt = BlockDB::get()["Dirt"].id;
    ChunkBlock stone = BlockDB::get()["Stone"].id;
    ChunkBlock grass = BlockDB::get()["Grass"].id;

    for (int x = 0; x < CHUNK_SIZE; ++x)
    for (int z = 0; z < CHUNK_SIZE; ++z)
    {
        chunk.setBlock(x, 0, z, stone);
        chunk.setBlock(x, 1, z, dirt);
        chunk.setBlock(x, 2, z, dirt);
        chunk.setBlock(x, 3, z, dirt);
        chunk.setBlock(x, 4, z, grass);
    }
}

int SuperFlatGenerator::getMinimumSpawnHeight() const noexcept
{
    return 1;
}
