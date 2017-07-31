#ifndef CHUNKBLOCK_H_INCLUDED
#define CHUNKBLOCK_H_INCLUDED

#include "BlockId.h"

class BlockDataHolder;
class BlockType;

struct ChunkBlock
{
    ChunkBlock() = default;

    ChunkBlock(Block_t id);
    ChunkBlock(BlockId id);

    const BlockDataHolder& getData() const;
    const BlockType& getType() const;

    bool operator ==(ChunkBlock other)
    {
        return id == other.id;
    }

    bool operator !=(ChunkBlock other)
    {
        return id != other.id;
    }

    Block_t id = 0;
};

#endif // CHUNKBLOCK_H_INCLUDED
