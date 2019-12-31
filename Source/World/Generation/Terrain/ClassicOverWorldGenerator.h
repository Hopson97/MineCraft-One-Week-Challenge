#ifndef CLASSICOVERWORLDGENERATOR_H_INCLUDED
#define CLASSICOVERWORLDGENERATOR_H_INCLUDED

#include "TerrainGenerator.h"

#include "../../../Util/Array2D.h"
#include "../../../Util/Random.h"

#include "../../../Maths/NoiseGenerator.h"
#include "../../WorldConstants.h"

#include "../Biome/DesertBiome.h"
#include "../Biome/GrasslandBiome.h"
#include "../Biome/LightForest.h"
#include "../Biome/OceanBiome.h"
#include "../Biome/TemperateForestBiome.h"

class Chunk;

class ClassicOverWorldGenerator : public TerrainGenerator {
  public:
    ClassicOverWorldGenerator();

    void generateTerrainFor(Chunk &chunk) override;
    int getMinimumSpawnHeight() const noexcept override;

  private:
    static void setUpNoise();

    void setBlocks(int maxHeight);

    void getHeightIn(int xMin, int zMin, int xMax, int zMax);
    void getHeightMap();
    void getBiomeMap();

    const Biome &getBiome(int x, int z) const;

    Array2D<int, CHUNK_SIZE> m_heightMap;
    Array2D<int, CHUNK_SIZE + 1> m_biomeMap;

    Random<std::minstd_rand> m_random;

    static NoiseGenerator m_biomeNoiseGen;

    GrasslandBiome m_grassBiome;
    TemperateForestBiome m_temperateForest;
    DesertBiome m_desertBiome;
    OceanBiome m_oceanBiome;
    LightForest m_lightForest;

    Chunk *m_pChunk = nullptr;
};

#endif // CLASSICOVERWORLDGENERATOR_H_INCLUDED
