#ifndef LIGHTFOREST_H_INCLUDED
#define LIGHTFOREST_H_INCLUDED

#include "Biome.h"

class LightForest : public Biome
{
    public:
        LightForest(int seed);

        ChunkBlock getPlant    (Rand& rand) const;
        ChunkBlock getTopBlock (Rand& rand) const;
        ChunkBlock getUnderWaterBlock   (Rand& rand) const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() ;
};

#endif // LIGHTFOREST_H_INCLUDED
