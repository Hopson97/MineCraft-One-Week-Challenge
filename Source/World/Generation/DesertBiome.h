#ifndef DESERTBIOME_H_INCLUDED
#define DESERTBIOME_H_INCLUDED

#include "Biome.h"

class DesertBiome : public Biome
{
    public:
        DesertBiome(int seed) noexcept;

        BlockId getTopBlock(Rand& rand) const noexcept;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;


    private:
        NoiseParameters getNoiseParameters() noexcept;
};

#endif // DESERTBIOME_H_INCLUDED
