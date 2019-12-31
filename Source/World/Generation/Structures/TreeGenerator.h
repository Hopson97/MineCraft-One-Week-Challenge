#ifndef TREEGENERATOR_H_INCLUDED
#define TREEGENERATOR_H_INCLUDED

#include "../../../Util/Random.h"

class Chunk;

void makeOakTree(Chunk &chunk, Random<std::minstd_rand> &rand, int x, int y,
                 int z);
void makePalmTree(Chunk &chunk, Random<std::minstd_rand> &rand, int x, int y,
                  int z);

void makeCactus(Chunk &chunk, Random<std::minstd_rand> &rand, int x, int y,
                int z);

#endif // TREEGENERATOR_H_INCLUDED
