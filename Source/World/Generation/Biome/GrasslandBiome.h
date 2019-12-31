#ifndef GRASSLANDBIOME_H_INCLUDED
#define GRASSLANDBIOME_H_INCLUDED

#include "Biome.h"

class GrasslandBiome : public Biome {
  public:
    GrasslandBiome(int seed);

    ChunkBlock getBeachBlock(Rand &rand) const override;
    ChunkBlock getPlant(Rand &rand) const override;
    ChunkBlock getTopBlock(Rand &rand) const override;
    ChunkBlock getUnderWaterBlock(Rand &rand) const override;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

  private:
    NoiseParameters getNoiseParameters() override;
};

#endif // GRASSLANDBIOME_H_INCLUDED
