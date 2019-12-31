#include "StructureBuilder.h"

#include "../../Chunk/Chunk.h"

#include <iostream>

void StructureBuilder::build(Chunk &chunk)
{
    for (auto &block : m_blocks) {
        chunk.setBlock(block.x, block.y, block.z, block.id);
    }
}

void StructureBuilder::makeColumn(int x, int z, int yStart, int height,
                                  BlockId block)
{
    for (int y = yStart; y < yStart + height; y++) {
        addBlock(x, y, z, block);
    }
}

void StructureBuilder::makeRowX(int xStart, int xEnd, int y, int z,
                                BlockId block)
{
    for (int x = xStart; x <= xEnd; ++x) {
        addBlock(x, y, z, block);
    }
}

void StructureBuilder::makeRowZ(int zStart, int zEnd, int x, int y,
                                BlockId block)
{
    for (int z = zStart; z <= zEnd; ++z) {
        addBlock(x, y, z, block);
    }
}

void StructureBuilder::fill(int y, int xStart, int xEnd, int zStart, int zEnd,
                            BlockId block)
{
    for (int x = xStart; x < xEnd; ++x)
        for (int z = zStart; z < zEnd; ++z) {
            addBlock(x, y, z, block);
        }
}

void StructureBuilder::addBlock(int x, int y, int z, BlockId block)
{
    m_blocks.emplace_back(block, x, y, z);
}
