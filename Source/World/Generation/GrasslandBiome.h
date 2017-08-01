#ifndef GRASSLANDBIOME_H_INCLUDED
#define GRASSLANDBIOME_H_INCLUDED

#include "Biome.h"

class GrasslandBiome : public Biome
{
    public:
        GrasslandBiome(int seed) noexcept;

        BlockId getTopBlock(Rand& rand) const noexcept;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() noexcept;
};

#endif // GRASSLANDBIOME_H_INCLUDED
