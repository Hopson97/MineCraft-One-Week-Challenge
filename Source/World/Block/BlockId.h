#ifndef BLOCKID_H_INCLUDED
#define BLOCKID_H_INCLUDED

#include <cstdint>

using Block_t = uint8_t;

enum class BlockId :  Block_t
{
    Air = 0,
    Grass,
    Dirt,
    Stone,
    OakBark,
    OakLeaf,

    NUM_TYPES
};



#endif // BLOCKID_H_INCLUDED
