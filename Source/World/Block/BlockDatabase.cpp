#include "BlockDatabase.h"

BlockDatabase::BlockDatabase()
    : textureAtlas("DefaultPack")
{
    m_blocks[(int)BlockId::Air] = std::make_unique<DefaultBlock>("Air");
    m_blocks[(int)BlockId::Grass] = std::make_unique<DefaultBlock>("Grass");
    m_blocks[(int)BlockId::Dirt] = std::make_unique<DefaultBlock>("Dirt");
    m_blocks[(int)BlockId::Stone] = std::make_unique<DefaultBlock>("Stone");
    m_blocks[(int)BlockId::OakBark] = std::make_unique<DefaultBlock>("OakBark");
    m_blocks[(int)BlockId::OakLeaf] = std::make_unique<DefaultBlock>("OakLeaf");
    m_blocks[(int)BlockId::Sand] = std::make_unique<DefaultBlock>("Sand");
    m_blocks[(int)BlockId::Water] = std::make_unique<DefaultBlock>("Water");
    m_blocks[(int)BlockId::Cactus] = std::make_unique<DefaultBlock>("Cactus");
    m_blocks[(int)BlockId::TallGrass] =
        std::make_unique<DefaultBlock>("TallGrass");
    m_blocks[(int)BlockId::Rose] = std::make_unique<DefaultBlock>("Rose");
    m_blocks[(int)BlockId::DeadShrub] =
        std::make_unique<DefaultBlock>("DeadShrub");
}

BlockDatabase &BlockDatabase::get()
{
    static BlockDatabase d;
    return d;
}

const BlockType &BlockDatabase::getBlock(BlockId id) const
{
    return *m_blocks[(int)id];
}

const BlockData &BlockDatabase::getData(BlockId id) const
{
    return m_blocks[(int)id]->getData();
}
