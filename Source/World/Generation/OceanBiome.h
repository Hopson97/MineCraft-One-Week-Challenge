#ifndef OCEANBIOME_H_INCLUDED
#define OCEANBIOME_H_INCLUDED

#include "Biome.h"

class OceanBiome : public Biome
{
    public:
        OceanBiome(int seed);

        BlockId getPlant    (Rand& rand) const;
        BlockId getTopBlock (Rand& rand) const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() ;
};

#endif // OCEANBIOME_H_INCLUDED
