#ifndef TEMPERATEFORESTBIOME_H_INCLUDED
#define TEMPERATEFORESTBIOME_H_INCLUDED

#include "Biome.h"

class TemperateForestBiome : public Biome
{
    public:
        TemperateForestBiome(int seed) noexcept;

        BlockId getTopBlock(Rand& rand) const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() noexcept;
};

#endif // TEMPERATEFORESTBIOME_H_INCLUDED
