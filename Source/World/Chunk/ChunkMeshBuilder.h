#ifndef CHUNKMESHBUILDER_H_INCLUDED
#define CHUNKMESHBUILDER_H_INCLUDED

class ChunkSection;
class ChunkMesh;

class ChunkMeshBuilder
{
    public:
        ChunkMeshBuilder(ChunkSection& chunk);

        void buildMesh(ChunkMesh& mesh);

    private:
        ChunkSection* m_pChunk;
        ChunkMesh*    m_pMesh;
};

#endif // CHUNKMESHBUILDER_H_INCLUDED
