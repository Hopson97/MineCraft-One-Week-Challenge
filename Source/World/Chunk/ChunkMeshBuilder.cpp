#include "ChunkMeshBuilder.h"

#include "ChunkSection.h"
#include "ChunkMesh.h"

#include "../Block/BlockData.h"
#include "../Block/BlockDatabase.h"

#include <vector>
#include <iostream>

namespace
{
    const std::vector<GLfloat> frontFace
    {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
    };

    const std::vector<GLfloat> backFace
    {
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
    };

    const std::vector<GLfloat> leftFace
    {
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,
    };

    const std::vector<GLfloat> rightFace
    {
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,
    };

    const std::vector<GLfloat> topFace
    {
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,
    };

    const std::vector<GLfloat> bottomFace
    {
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1
    };

}

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunk)
:   m_pChunk    (&chunk)
{ }

struct Directions
{
    void update(int x, int y, int z)
    {
        up      =   {x,     y + 1,  z};
        down    =   {x,     y - 1,  z};
        left    =   {x - 1, y,      z};
        right   =   {x + 1, y,      z};
        front   =   {x,     y,      z + 1};
        back    =   {x,     y,      z - 1};
    }

    sf::Vector3i up;
    sf::Vector3i down;
    sf::Vector3i left;
    sf::Vector3i right;
    sf::Vector3i front;
    sf::Vector3i back;
};

int faces = 0;

void ChunkMeshBuilder::buildMesh(ChunkMesh& mesh)
{
    sf::Clock c;
    std::cout << "Begin mesh build\n";
    m_pMesh = &mesh;

    Directions directions;

    for (int8_t y = 0; y < CHUNK_SIZE; ++y)
    for (int8_t x = 0; x < CHUNK_SIZE; ++x)
    for (int8_t z = 0; z < CHUNK_SIZE; ++z)
    {
        sf::Vector3i position(x, y, z);
        auto  block = m_pChunk->getBlock(x, y, z);
        if (block == 0)
        {
            continue;
        }

        m_pBlockData = &block.getData().getBlockData();
        auto& data = *m_pBlockData;
        directions.update(x, y, z);

        tryAddFaceToMesh(topFace,       data.texTopCoord,       position, directions.up);
        tryAddFaceToMesh(bottomFace,    data.texBottomCoord,    position, directions.down);
        tryAddFaceToMesh(leftFace,      data.texSideCoord,      position, directions.left);
        tryAddFaceToMesh(rightFace,     data.texSideCoord,      position, directions.right);
        tryAddFaceToMesh(frontFace,     data.texSideCoord,      position, directions.front);
        tryAddFaceToMesh(backFace,      data.texSideCoord,      position, directions.back);
    }
    std::cout << "End mesh build, faces: " << faces << " Time: " << c.getElapsedTime().asMilliseconds() << "ms\n";
}

void ChunkMeshBuilder::tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
                                        const sf::Vector2i& textureCoords,
                                        const sf::Vector3i& blockPosition,
                                        const sf::Vector3i& blockFacing)
{
    if (shouldMakeFace(blockFacing, *m_pBlockData))
    {
        faces++;
        auto texCoords = BlockDatabase::get().textureAtlas.getTexture(textureCoords);

        m_pMesh->addFace(blockFace, texCoords, m_pChunk->getLocation(), blockPosition);
    }
}


bool ChunkMeshBuilder::shouldMakeFace(const sf::Vector3i& adjBlock,
                                      const BlockDataHolder& blockData)
{
    auto block = m_pChunk->getBlock(adjBlock.x, adjBlock.y, adjBlock.z);
    //auto& data  = block.getData();

    if (block == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    ///@TODO Transparent Blocks
}












