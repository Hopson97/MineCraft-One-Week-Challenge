#ifndef STRUCTUREBUILDER_H_INCLUDED
#define STRUCTUREBUILDER_H_INCLUDED

#include <vector>
// #include "../../Block/Block.h"

class Chunk;

class StructureBuilder
{
    struct Block
    {
        Block(unsigned id, int x, int y, int z)
        :   id  (id)
        ,   x   (x)
        ,   y   (y)
        ,   z   (z)
        { }

        unsigned id;
        int x, y, z;
    };

    public:
        void build(Chunk& chunk);

        void makeColumn(int x, int z, int yStart, int height, unsigned block);
        void makeRowX   (int xStart, int xEnd, int y, int z, unsigned block);
        void makeRowZ   (int zStart, int zEnd, int x, int y, unsigned block);

        void fill (int y, int xStart, int xEnd, int zStart, int zEnd, unsigned block);

        void addBlock(int x, int y, int z, unsigned block);


    private:
        std::vector<Block> m_blocks;

};

#endif // STRUCTUREBUILDER_H_INCLUDED
