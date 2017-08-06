#ifndef DESERTBIOME_H_INCLUDED
#define DESERTBIOME_H_INCLUDED

#include "Biome.h"

class DesertBiome : public Biome
{
    public:
        DesertBiome(int seed) ;

        ChunkBlock getPlant    (Rand& rand) const;
        ChunkBlock getTopBlock (Rand& rand) const;
        ChunkBlock getUnderWaterBlock   (Rand& rand) const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() ;
};

#endif // DESERTBIOME_H_INCLUDED
