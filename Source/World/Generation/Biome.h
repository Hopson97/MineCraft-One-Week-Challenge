#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockId.h"

using Rand = Random<std::minstd_rand>;

class Chunk;

struct Biome
{
    public:
        Biome(const NoiseParameters& parameters, int treeFreq, int plantFreq, int seed);

        virtual BlockId getPlant    (Rand& rand) const = 0;
        virtual BlockId getTopBlock (Rand& rand) const = 0;
        virtual void makeTree       (Rand& rand, Chunk& chunk, int x, int y, int z) const = 0;


        int getHeight(int x, int z, int chunkX, int chunkZ) const;
        int getTreeFrequency    () const noexcept;
        int getPlantFrequency   () const noexcept;

    protected:
        virtual NoiseParameters getNoiseParameters() = 0;

    private:
        NoiseGenerator m_heightGenerator;
        int m_treeFreq;
        int m_plantFreq;
};

#endif // BIOME_H_INCLUDED
