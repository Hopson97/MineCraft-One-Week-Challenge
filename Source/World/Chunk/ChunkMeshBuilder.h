#ifndef CHUNKMESHBUILDER_H_INCLUDED
#define CHUNKMESHBUILDER_H_INCLUDED

#include "../../glad/glad.h"
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Block/ChunkBlock.h"

class ChunkSection;
class ChunkMesh;
class BlockData;

struct ChunkMeshCollection;
struct BlockDataHolder;

class ChunkMeshBuilder {
  public:
    ChunkMeshBuilder(ChunkSection &chunk, ChunkMeshCollection &meshes);

    void buildMesh();

  private:
    void setActiveMesh(ChunkBlock block);

    void addXBlockToMesh(const sf::Vector2i &textureCoords,
                         const sf::Vector3i &blockPosition);

    void tryAddFaceToMesh(const std::array<GLfloat, 12> &blockFace,
                          const sf::Vector2i &textureCoords,
                          const sf::Vector3i &blockPosition,
                          const sf::Vector3i &blockFacing,
                          GLfloat cardinalLight);

    bool shouldMakeFace(const sf::Vector3i &blockPosition,
                        const BlockDataHolder &blockData);

    bool shouldMakeLayer(int y);

    const ChunkBlock *m_pBlockPtr = nullptr;
    ChunkSection *m_pChunk = nullptr;
    ChunkMeshCollection *m_pMeshes = nullptr;
    ChunkMesh *m_pActiveMesh = nullptr;
    const BlockDataHolder *m_pBlockData = nullptr;
};

#endif // CHUNKMESHBUILDER_H_INCLUDED
