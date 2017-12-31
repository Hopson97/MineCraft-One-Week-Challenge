#ifndef CHUNKBLOCK_H_INCLUDED
#define CHUNKBLOCK_H_INCLUDED

#include "Block.h"

// struct BlockDataHolder;
// class BlockType;

struct ChunkBlock
{
    ChunkBlock() = default;

    ChunkBlock(unsigned id);

    const Block& getData() const;

    bool operator ==(ChunkBlock other) const
    {
        return id == other.id;
    }

    bool operator !=(ChunkBlock other) const
    {
        return id != other.id;
    }

    unsigned id = 0;
};

#endif // CHUNKBLOCK_H_INCLUDED
