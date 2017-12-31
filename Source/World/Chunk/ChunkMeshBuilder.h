#ifndef CHUNKMESHBUILDER_H_INCLUDED
#define CHUNKMESHBUILDER_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "../Block/ChunkBlock.h"
#include "../Block/BlockDB.h"

class ChunkSection;
class ChunkMesh;
// class BlockData;

struct ChunkMeshCollection;
// struct BlockDataHolder;

class ChunkMeshBuilder
{
    public:
        ChunkMeshBuilder(ChunkSection& chunk, ChunkMeshCollection& meshes);

        void buildMesh();

    private:
        void setActiveMesh(ChunkBlock block);

        void addXBlockToMesh(const sf::Vector2i& textureCoords,
                             const sf::Vector3i& blockPosition);

        void tryAddFaceToMesh(const std::array<GLfloat, 12>& blockFace,
                              const sf::Vector2i& textureCoords,
                              const sf::Vector3i& blockPosition,
                              const sf::Vector3i& blockFacing,
                              GLfloat cardinalLight);

        bool shouldMakeFace (const sf::Vector3i& blockPosition,
                             const Block& block);

        bool shouldMakeLayer(int y);

        const ChunkBlock*       m_pBlockPtr = nullptr;
        ChunkSection*           m_pChunk    = nullptr;
        ChunkMeshCollection*    m_pMeshes   = nullptr;
        ChunkMesh*              m_pActiveMesh   = nullptr;
        const Block*            m_pBlock    = nullptr;

};

#endif // CHUNKMESHBUILDER_H_INCLUDED
