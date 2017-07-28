#include "BlockDatabase.h"


BlockDatabase::BlockDatabase()
{
    m_blocks[(int)BlockId::Air]     = std::make_unique<DefaultBlock>("Air");
    m_blocks[(int)BlockId::Grass]   = std::make_unique<DefaultBlock>("Grass");
    m_blocks[(int)BlockId::Dirt]    = std::make_unique<DefaultBlock>("Dirt");
    m_blocks[(int)BlockId::Stone]   = std::make_unique<DefaultBlock>("Stone");
}

BlockDatabase& BlockDatabase::get()
{
    static BlockDatabase d;
    return d;
}

const BlockType& BlockDatabase::getBlock(BlockId id) const
{
    return *m_blocks[(int)id];
}

const BlockData& BlockDatabase::getData(BlockId id) const
{
    return m_blocks[(int)id]->getData();
}


