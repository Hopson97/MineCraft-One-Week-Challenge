#ifndef TERRAINGENERATOR_H_INCLUDED
#define TERRAINGENERATOR_H_INCLUDED

#include <array>

#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"
#include "../../Util/Random.h"

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

        void getHeightMap();
        void getBiomeMap ();

        std::array<int, CHUNK_AREA> m_heightMap;
        std::array<int, CHUNK_AREA> m_biomeMap;

        Random<std::minstd_rand> m_random;

        static NoiseGenerator m_heightNoiseGen;
        static NoiseGenerator m_biomeNoiseGen;



        Chunk* m_pChunk = nullptr;
};


#endif // TERRAINGENERATOR_H_INCLUDED
