#include "ChunkBlock.h"

#include "BlockDB.h"

ChunkBlock::ChunkBlock(unsigned id)
:   id  (id)
{

}


const Block& ChunkBlock::getData() const
{
    return BlockDB::get()[id];
}

/*const BlockType& ChunkBlock::getType() const
{
    return BlockDatabase::get().getBlock((BlockId)id);
}*/
