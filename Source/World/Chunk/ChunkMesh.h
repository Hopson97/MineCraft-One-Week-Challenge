#ifndef CHUNKMESH_H_INCLUDED
#define CHUNKMESH_H_INCLUDED

#include "../../Model.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

class ChunkMesh {
  public:
    ChunkMesh() = default;

    void addFace(const std::array<GLfloat, 12> &blockFace,
                 const std::array<GLfloat, 8> &textureCoords,
                 const sf::Vector3i &chunkPosition,
                 const sf::Vector3i &blockPosition, GLfloat cardinalLight);

    void bufferMesh();

    const Model &getModel() const;

    void deleteData();

    int faces = 0;

  private:
    Mesh m_mesh;
    Model m_model;
    std::vector<GLfloat> m_light;
    GLuint m_indexIndex = 0;
};

struct ChunkMeshCollection {
    ChunkMesh solidMesh;
    ChunkMesh waterMesh;
    ChunkMesh floraMesh;
};

#endif // CHUNKMESH_H_INCLUDED
