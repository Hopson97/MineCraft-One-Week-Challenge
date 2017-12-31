#include "ChunkMeshBuilder.h"

#include "ChunkSection.h"
#include "ChunkMesh.h"

// #include "../Block/BlockData.h"
// #include "../Block/BlockDatabase.h"

#include <vector>
#include <iostream>
#include <cassert>

namespace
{
    const std::array<GLfloat, 12> frontFace
    {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
    };

    const std::array<GLfloat, 12> backFace
    {
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
    };

    const std::array<GLfloat, 12> leftFace
    {
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,
    };

    const std::array<GLfloat, 12> rightFace
    {
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,
    };

    const std::array<GLfloat, 12> topFace
    {
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,
    };

    const std::array<GLfloat, 12> bottomFace
    {
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1
    };

    const std::array<GLfloat, 12> xFace1
    {
        0, 0, 0,
        1, 0, 1,
        1, 1, 1,
        0, 1, 0,
    };

    const std::array<GLfloat, 12> xFace2
    {
        0, 0, 1,
        1, 0, 0,
        1, 1, 0,
        0, 1, 1,
    };

    constexpr GLfloat LIGHT_TOP = 1.0f;
    constexpr GLfloat LIGHT_LEFT   = 0.9f;
    constexpr GLfloat LIGHT_RIGHT   = 0.8f;
    constexpr GLfloat LIGHT_BACK = 0.7f;
    constexpr GLfloat LIGHT_FRONT   = 0.6f;
    constexpr GLfloat LIGHT_BOT = 0.5f;
}

ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunk, ChunkMeshCollection& mesh)
:   m_pChunk    (&chunk)
,   m_pMeshes   (&mesh)
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
    AdjacentBlockPositions directions;
    m_pBlockPtr = m_pChunk->begin();
    faces = 0;
    for (int8_t y = 0; y < CHUNK_SIZE; ++y)
    {
        //ChunkBlock block = *blockPointer;
        //blockPointer++;

        if (!shouldMakeLayer(y))
            continue;

        for (int8_t z = 0; z < CHUNK_SIZE; ++z)
        for (int8_t x = 0; x < CHUNK_SIZE; ++x)
        {
            ChunkBlock block = *m_pBlockPtr;
            m_pBlockPtr++;

            sf::Vector3i position(x, y, z);
            setActiveMesh(block);

            if (block == 0/*Nothing*/)
            {
                continue;
            }

            m_pBlock = &block.getData();
            auto& data = *m_pBlock;

            if (data.meshType == BlockMeshType::X)
            {
                addXBlockToMesh(data.texTopCoord, position);
                continue;
            }


            directions.update(x, y, z);

            //Up/ Down
            if (((m_pChunk->getLocation().y != 0) || y != 0) && data.id != 1) 
                tryAddFaceToMesh(bottomFace, data.texBottomCoord,   position, directions.down, LIGHT_BOT);

            tryAddFaceToMesh(topFace,    data.texTopCoord,          position, directions.up, LIGHT_TOP);
            
            
            //Left/ Right
            if(data.id != 1){
            tryAddFaceToMesh(leftFace,  data.texSideCoord, position, directions.left,   LIGHT_LEFT);
            tryAddFaceToMesh(rightFace, data.texSideCoord, position, directions.right,  LIGHT_RIGHT);

            //Front/ Back
            tryAddFaceToMesh(frontFace, data.texSideCoord, position, directions.front, LIGHT_FRONT);
            tryAddFaceToMesh(backFace,  data.texSideCoord, position, directions.back,  LIGHT_BACK);
            }
        }
    }
}

void ChunkMeshBuilder::setActiveMesh(ChunkBlock block)
{
    switch (block.getData().shaderType)
    {
        case BlockShaderType::Chunk:
            m_pActiveMesh = &m_pMeshes->solidMesh;
            break;

        case BlockShaderType::Liquid:
            m_pActiveMesh = &m_pMeshes->waterMesh;
            break;

        case BlockShaderType::Flora:
            m_pActiveMesh = &m_pMeshes->floraMesh;
            break;
    }
}

void ChunkMeshBuilder::addXBlockToMesh(const sf::Vector2i& textureCoords,
                                       const sf::Vector3i& blockPosition)
{
    faces++;
    auto texCoords = BlockDB::get().textureAtlas.getTexture(textureCoords);

    m_pActiveMesh->addFace( xFace1,
                            texCoords,
                            m_pChunk->getLocation(),
                            blockPosition,
                            LIGHT_LEFT);

    m_pActiveMesh->addFace( xFace2,
                        texCoords,
                        m_pChunk->getLocation(),
                        blockPosition,
                        LIGHT_RIGHT);
}


void ChunkMeshBuilder::tryAddFaceToMesh(const std::array<GLfloat, 12>& blockFace,
                                        const sf::Vector2i& textureCoords,
                                        const sf::Vector3i& blockPosition,
                                        const sf::Vector3i& blockFacing,
                                        GLfloat cardinalLight)
{
    if (shouldMakeFace(blockFacing, *m_pBlock))
    {
        faces++;
        auto texCoords = BlockDB::get().textureAtlas.getTexture(textureCoords);

        m_pActiveMesh->addFace( blockFace,
                                texCoords,
                                m_pChunk->getLocation(),
                                blockPosition,
                                cardinalLight);
    }
}


bool ChunkMeshBuilder::shouldMakeFace(const sf::Vector3i& adjBlock,
                                      const Block& block)
{
    auto chunkblock = m_pChunk->getBlock(adjBlock.x, adjBlock.y, adjBlock.z);
    auto& data  = chunkblock.getData();

    auto upblock = m_pChunk->getBlock(adjBlock.x, adjBlock.y + 1, adjBlock.z);
    auto& udata = upblock.getData();
    if(udata.id != block.id){
        return true;
    }

    if (chunkblock == 1/*Air*/)
    {
        return true;
    }
    else if ((!data.isOpaque) && (data.id != m_pBlock->id))
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



