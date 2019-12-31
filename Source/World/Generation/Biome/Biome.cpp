#include "Biome.h"

Biome::Biome(const NoiseParameters &parameters, int treeFreq, int plantFreq,
             int seed)
    : m_heightGenerator(seed)
    , m_treeFreq(treeFreq)
    , m_plantFreq(plantFreq)
{
    m_heightGenerator.setParameters(parameters);
}

ChunkBlock Biome::getBeachBlock(Rand &rand) const
{
    return BlockId::Sand;
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const
{
    return m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int Biome::getTreeFrequency() const noexcept
{
    return m_treeFreq;
}

int Biome::getPlantFrequency() const noexcept
{
    return m_plantFreq;
}
