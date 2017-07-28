#ifndef CHUNKMESH_H_INCLUDED
#define CHUNKMESH_H_INCLUDED

#include "../../Model.h"

#include <vector>

class ChunkMesh
{
    public:
        ChunkMesh();

        void addFace(const Mesh& mesh);

    private:
        Mesh  m_mesh;
        Model m_model;
};

#endif // CHUNKMESH_H_INCLUDED
