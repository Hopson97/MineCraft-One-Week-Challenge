#ifndef CHUNKBLOCK_H_INCLUDED
#define CHUNKBLOCK_H_INCLUDED

#include "BlockId.h"

class BlockData;
class BlockType;

struct ChunkBlock
{
    ChunkBlock() = default;

    ChunkBlock(Block_t id);
    ChunkBlock(BlockId id);

    const BlockData& getData() const;
    const BlockType& getType() const;

    bool operator ==(ChunkBlock other)
    {
        return id == other.id;
    }

    Block_t id = 1;
};

#endif // CHUNKBLOCK_H_INCLUDED
