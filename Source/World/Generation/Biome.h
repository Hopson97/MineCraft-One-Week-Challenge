#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockId.h"

using Rand = Random<std::minstd_rand>;

class Chunk;

struct IBiome
{
    virtual BlockId getTopBlock(Rand& rand) = 0;
    virtual void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) = 0;

    virtual int getHeight(int x, int z, int chunkX, int chunkZ) = 0;
    virtual int getTreeFrequency();
};

class GrasslandBiome : public IBiome
{
    public:
        GrasslandBiome(int seed);

        BlockId getTopBlock(Rand& rand);
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z);

        int getHeight(int x, int z, int chunkX, int chunkZ);

        int getTreeFrequency();

    private:
        NoiseGenerator m_heightGenerator;
};

class LightForestBiome : public IBiome
{
    public:
        LightForestBiome(int seed);

        BlockId getTopBlock(Rand& rand);
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z);

        int getHeight(int x, int z, int chunkX, int chunkZ);

        int getTreeFrequency();

    private:
        NoiseGenerator m_heightGenerator;
};

class DesertBiome : public IBiome
{
    public:
        DesertBiome(int seed);

        BlockId getTopBlock(Rand& rand);
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z);

        int getHeight(int x, int z, int chunkX, int chunkZ);

        int getTreeFrequency();

    private:
        NoiseGenerator m_heightGenerator;
};

#endif // BIOME_H_INCLUDED
