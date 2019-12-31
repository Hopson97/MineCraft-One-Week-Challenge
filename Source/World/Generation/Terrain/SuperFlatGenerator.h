#ifndef SUPERFLATGENERATOR_H_INCLUDED
#define SUPERFLATGENERATOR_H_INCLUDED

#include "TerrainGenerator.h"

class SuperFlatGenerator : public TerrainGenerator {
  public:
    void generateTerrainFor(Chunk &chunk) override;
    int getMinimumSpawnHeight() const noexcept override;
};

#endif // SUPERFLATGENERATOR_H_INCLUDED
