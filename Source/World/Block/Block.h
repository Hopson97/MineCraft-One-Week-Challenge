#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <SFML/Graphics.hpp>

enum class BlockMeshType {
	Cube = 0,
	X = 1,
};

enum class BlockShaderType
{
    Chunk   = 0,
    Liquid  = 1,
    Flora   = 2,
};

class Block
{
    public:
        bool isOpaque;
        bool isCollidable;
        bool isBlock;
        unsigned id; // Identifies a block type
        int maxStackSize;
        BlockMeshType meshType;
        BlockShaderType shaderType;
        std::string name;
        // std::string description;
        sf::Vector2i texTopCoord;
        sf::Vector2i texSideCoord;
        sf::Vector2i texBottomCoord;
};

#endif // BLOCK_H
