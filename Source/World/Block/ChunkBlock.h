#ifndef CHUNKBLOCK_H_INCLUDED
#define CHUNKBLOCK_H_INCLUDED

#include "BlockId.h"

struct ChunkBlock
{
    ChunkBlock() = default;

    ChunkBlock(Block_t id);
    ChunkBlock(BlockId id);

    Block_t id = 0;
};

#endif // CHUNKBLOCK_H_INCLUDED
