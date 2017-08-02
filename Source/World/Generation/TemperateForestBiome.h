#ifndef TEMPERATEFORESTBIOME_H_INCLUDED
#define TEMPERATEFORESTBIOME_H_INCLUDED

#include "Biome.h"

class TemperateForestBiome : public Biome
{
    public:
        TemperateForestBiome(int seed) ;

        BlockId getPlant    (Rand& rand) const;
        BlockId getTopBlock (Rand& rand) const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() ;
};

#endif // TEMPERATEFORESTBIOME_H_INCLUDED
