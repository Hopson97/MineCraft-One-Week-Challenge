#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

struct Mesh
{
    std::vector<GLfloat> vertexPositions;
    std::vector<GLfloat> textureCoords;
    std::vector<GLuint>  indices;
};

#endif // MESH_H_INCLUDED
