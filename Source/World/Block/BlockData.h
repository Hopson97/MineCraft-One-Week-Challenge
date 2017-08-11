#ifndef BLOCKDATA_H_INCLUDED
#define BLOCKDATA_H_INCLUDED

#include "../../Util/NonCopyable.h"
#include "BlockId.h"
#include <SFML/Graphics.hpp>

enum class BlockMeshType
{
    Cube = 0,
    X = 1,
};

struct BlockDataHolder : public NonCopyable
{
    BlockId      id;
    sf::Vector2i texTopCoord;
    sf::Vector2i texSideCoord;
    sf::Vector2i texBottomCoord;

    BlockMeshType meshType;

    bool isOpaque;
};

class BlockData : public NonCopyable
{
    public:
        BlockData(const std::string& fileName);

        const BlockDataHolder& getBlockData() const;

    private:
        BlockDataHolder m_data;

};

#endif // BLOCKDATA_H_INCLUDED
