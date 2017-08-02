#include "ChunkMeshBuilder.h"

#include "ChunkSection.h"
#include "ChunkMesh.h"

#include "../Block/BlockData.h"
#include "../Block/BlockDatabase.h"

#include <vector>
#include <iostream>
#include <cassert>

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

    constexpr GLfloat LIGHT_TOP = 1.0f;
    constexpr GLfloat LIGHT_X   = 0.8f;
    constexpr GLfloat LIGHT_Z   = 0.6f;
    constexpr GLfloat LIGHT_BOT = 0.4f;

}

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunk, ChunkMesh& mesh)
:   m_pChunk    (&chunk)
,   m_pMesh     (&mesh)
{ }

struct AdjacentBlockPositions
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

int faces;
void ChunkMeshBuilder::buildMesh()
{
    sf::Clock c;
    //std::cout << "Begin mesh build\n";

    AdjacentBlockPositions directions;

    faces = 0;
    for (int8_t y = 0; y < CHUNK_SIZE; ++y)
    {
        if (!shouldMakeLayer(y))
            continue;

        for (int8_t x = 0; x < CHUNK_SIZE; ++x)
        for (int8_t z = 0; z < CHUNK_SIZE; ++z)
        {
            sf::Vector3i position(x, y, z);
            ChunkBlock   block = m_pChunk->getBlock(x, y, z);

            if (block == BlockId::Air)
            {
                continue;
            }

            m_pBlockData = &block.getData();
            auto& data = *m_pBlockData;
            directions.update(x, y, z);


            //Up/ Down
            //if ((y == 0) && (m_pChunk->getLocation().y == 0))
            tryAddFaceToMesh(bottomFace, data.texBottomCoord,    position, directions.down, LIGHT_BOT);
            tryAddFaceToMesh(topFace,    data.texTopCoord,       position, directions.up, LIGHT_TOP);

            //Left/ Right
            tryAddFaceToMesh(leftFace,  data.texSideCoord, position, directions.left,  LIGHT_X);
            tryAddFaceToMesh(rightFace, data.texSideCoord, position, directions.right, LIGHT_X);

            //Front/ Back
            tryAddFaceToMesh(frontFace, data.texSideCoord, position, directions.front, LIGHT_Z);
            tryAddFaceToMesh(backFace,  data.texSideCoord, position, directions.back,  LIGHT_Z);
        }
    }
/*
    std::cout   << "End mesh build, faces:  " << faces << '\n'
                << "Time:                   " << c.getElapsedTime().asSeconds() * 1000 << "ms" << '\n'
                << "Y:                      " << m_pChunk->getLocation().y <<  "\n\n";
*/
}

void ChunkMeshBuilder::tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
                                        const sf::Vector2i& textureCoords,
                                        const sf::Vector3i& blockPosition,
                                        const sf::Vector3i& blockFacing,
                                        GLfloat cardinalLight)
{
    if (shouldMakeFace(blockFacing, *m_pBlockData))
    {
        faces++;
        auto texCoords = BlockDatabase::get().textureAtlas.getTexture(textureCoords);

        m_pMesh->addFace(blockFace,
                         texCoords,
                         m_pChunk->getLocation(),
                         blockPosition,
                         cardinalLight);
    }
}


bool ChunkMeshBuilder::shouldMakeFace(const sf::Vector3i& adjBlock,
                                      const BlockDataHolder& blockData)
{
    auto block = m_pChunk->getBlock(adjBlock.x, adjBlock.y, adjBlock.z);
    auto& data  = block.getData();

    if (block == BlockId::Air)
    {
        return true;
    }
    else if ((!data.isOpaque) && (data.id != m_pBlockData->id))
    {
        return true;
    }
    return false;
}

bool ChunkMeshBuilder::shouldMakeLayer(int y)
{
    auto adjIsSolid = [&](int dx, int dz)
    {
        const ChunkSection& sect = m_pChunk->getAdjacent(dx, dz);
        return sect.getLayer(y).isAllSolid();
    };

    return  (!m_pChunk->getLayer(y    ).isAllSolid()) ||
            (!m_pChunk->getLayer(y + 1).isAllSolid()) ||
            (!m_pChunk->getLayer(y - 1).isAllSolid()) ||

            (!adjIsSolid( 1,  0)) ||
            (!adjIsSolid( 0,  1)) ||
            (!adjIsSolid(-1,  0)) ||
            (!adjIsSolid( 0, -1));

}



