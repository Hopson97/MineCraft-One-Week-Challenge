#ifndef GRASSLANDBIOME_H_INCLUDED
#define GRASSLANDBIOME_H_INCLUDED

#include "Biome.h"

class GrasslandBiome : public Biome
{
    public:
        GrasslandBiome(int seed);

        BlockId getPlant    (Rand& rand) const;
        BlockId getTopBlock (Rand& rand) const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() ;
};

#endif // GRASSLANDBIOME_H_INCLUDED
