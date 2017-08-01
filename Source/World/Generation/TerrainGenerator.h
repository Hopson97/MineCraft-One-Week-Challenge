#ifndef TERRAINGENERATOR_H_INCLUDED
#define TERRAINGENERATOR_H_INCLUDED

#include <array>

#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"

class Chunk;

class TerrainGenerator
{
    public:
        TerrainGenerator();

        void generateTerrainFor (Chunk& chunk);

    private:
        void setBlocks();
        void setTopBlock(int x, int y, int z);

        std::array<int, CHUNK_AREA> getHeightMap();
        std::array<int, CHUNK_AREA> getBiomeMap ();

        static void setUpNoise();

        static NoiseGenerator m_heightNoiseGen;
        static NoiseGenerator m_biomeNoiseGen;

        Chunk* m_pChunk = nullptr;
};


#endif // TERRAINGENERATOR_H_INCLUDED
