#ifndef LIGHTFOREST_H_INCLUDED
#define LIGHTFOREST_H_INCLUDED

#include "Biome.h"

class LightForest : public Biome {
  public:
    LightForest(int seed);

    ChunkBlock getPlant(Rand &rand) const override;
    ChunkBlock getTopBlock(Rand &rand) const override;
    ChunkBlock getUnderWaterBlock(Rand &rand) const override;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

  private:
    NoiseParameters getNoiseParameters() override;
};

#endif // LIGHTFOREST_H_INCLUDED
