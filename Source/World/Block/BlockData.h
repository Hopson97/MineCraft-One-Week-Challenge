#ifndef BLOCKDATA_H_INCLUDED
#define BLOCKDATA_H_INCLUDED 1

#include "../../Util/NonCopyable.h"
#include "BlockId.h"
#include <SFML/Graphics.hpp>

/// @brief Allocates meshes to cubes and non-cube entities.
enum class BlockMeshType {
    Cube = 0,
    X = 1,
};

/// @brief Allocates shader behavior to groups of blocks.
enum class BlockShaderType {
    Chunk = 0,
    Liquid = 1,
    Flora = 2,
};

/// @brief Struct designed to hold geometric and tangibility data for each individual block.
struct BlockDataHolder : public NonCopyable {
    BlockId id;
    sf::Vector2i texTopCoord;
    sf::Vector2i texSideCoord;
    sf::Vector2i texBottomCoord;

    BlockMeshType meshType;
    BlockShaderType shaderType;

    bool isOpaque;
    bool isCollidable;
};

class BlockData : public NonCopyable {
  public:
    BlockData(const std::string &fileName);

    const BlockDataHolder &getBlockData() const;

  private:
    BlockDataHolder m_data;
};

#endif // BLOCKDATA_H_INCLUDED
