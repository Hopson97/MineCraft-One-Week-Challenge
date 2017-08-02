#ifndef TERRAINGENERATOR_H_INCLUDED
#define TERRAINGENERATOR_H_INCLUDED

#include "../../Util/Array2D.h"
#include "../../Util/Random.h"

#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"


#include "GrasslandBiome.h"
#include "TemperateForestBiome.h"
#include "DesertBiome.h"
#include "OceanBiome.h"

class Chunk;

class TerrainGenerator
{
    public:
        TerrainGenerator();

        void generateTerrainFor (Chunk& chunk);

    private:
        static void setUpNoise();

        void setBlocks(int maxHeight);
        void setTopBlock(int x, int y, int z);

        void getHeightIn (int xMin, int zMin, int xMax, int zMax);
        void getHeightMap();
        void getBiomeMap ();

        const Biome& getBiome(int x, int z) const;

        Array2D<int, CHUNK_SIZE>        m_heightMap;
        Array2D<int, CHUNK_SIZE + 1>    m_biomeMap;

        Random<std::minstd_rand> m_random;

        static NoiseGenerator m_biomeNoiseGen;

        GrasslandBiome          m_grassBiome;
        TemperateForestBiome    m_lightForest;
        DesertBiome             m_desertBiome;
        OceanBiome              m_oceanBiome;

        Chunk* m_pChunk = nullptr;
};




#endif // TERRAINGENERATOR_H_INCLUDED
