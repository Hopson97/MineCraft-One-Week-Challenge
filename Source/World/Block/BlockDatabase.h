#ifndef BLOCKDATABASE_H_INCLUDED
#define BLOCKDATABASE_H_INCLUDED

#include <array>
#include <memory>

#include "../../Util/Singleton.h"

#include "BlockId.h"
#include "BlockTypes/BlockType.h"

#include "../../Texture/TextureAtlas.h"

/// @brief Singleton class that determines status and ID of blocks as a whole.
class BlockDatabase : public Singleton {
  public:
    static BlockDatabase &get();

    const BlockType &getBlock(BlockId id) const;
    const BlockData &getData(BlockId id) const;

    TextureAtlas textureAtlas;

  private:
    BlockDatabase();

    std::array<std::unique_ptr<BlockType>, (unsigned)BlockId::NUM_TYPES>
        m_blocks;
};

#endif // BLOCKDATABASE_H_INCLUDED
