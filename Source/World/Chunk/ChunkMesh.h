#ifndef CHUNKMESH_H_INCLUDED
#define CHUNKMESH_H_INCLUDED

#include "../../Model.h"

#include <vector>

class ChunkMesh
{
    public:
        ChunkMesh();

        void addFace();

    private:
        std::vector<GLfloat> textureCoords
};

#endif // CHUNKMESH_H_INCLUDED
