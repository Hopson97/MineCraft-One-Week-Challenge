#include "ChunkMesh.h"

#include "../WorldConstants.h"

#include <iostream>

void ChunkMesh::addFace(const std::array<GLfloat, 12> &blockFace,
                        const std::array<GLfloat, 8> &textureCoords,
                        const sf::Vector3i &chunkPosition,
                        const sf::Vector3i &blockPosition,
                        GLfloat cardinalLight)
{
    faces++;
    auto &verticies = m_mesh.vertexPositions;
    auto &texCoords = m_mesh.textureCoords;
    auto &indices = m_mesh.indices;

    texCoords.insert(texCoords.end(), textureCoords.begin(),
                     textureCoords.end());

    /// Vertex: The current vertex in the "blockFace" vector, 4 vertex in total
    /// hence "< 4" Index: X, Y, Z
    for (int i = 0, index = 0; i < 4; ++i) {
        verticies.push_back(blockFace[index++] + chunkPosition.x * CHUNK_SIZE +
                            blockPosition.x);
        verticies.push_back(blockFace[index++] + chunkPosition.y * CHUNK_SIZE +
                            blockPosition.y);
        verticies.push_back(blockFace[index++] + chunkPosition.z * CHUNK_SIZE +
                            blockPosition.z);
        m_light.push_back(cardinalLight);
    }

    indices.insert(indices.end(),
                   {m_indexIndex, m_indexIndex + 1, m_indexIndex + 2,

                    m_indexIndex + 2, m_indexIndex + 3, m_indexIndex});
    m_indexIndex += 4;
}

void ChunkMesh::bufferMesh()
{
    m_model.addData(m_mesh);
    m_model.addVBO(1, m_light);

    m_mesh.vertexPositions.clear();
    m_mesh.textureCoords.clear();
    m_mesh.indices.clear();
    m_light.clear();

    m_mesh.vertexPositions.shrink_to_fit();
    m_mesh.textureCoords.shrink_to_fit();
    m_mesh.indices.shrink_to_fit();
    m_light.shrink_to_fit();

    m_indexIndex = 0;
}

void ChunkMesh::deleteData()
{
    m_model.deleteData();
}

const Model &ChunkMesh::getModel() const
{
    return m_model;
}
