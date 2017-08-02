#include "Biome.h"

Biome::Biome(const NoiseParameters& parameters, int treeFreq, int seed)
:   m_heightGenerator   (seed)
,   m_treeFreq          (treeFreq)
{
    m_heightGenerator.setParameters(parameters);
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const
{
    return m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int Biome::getTreeFrequency() const
{
    return m_treeFreq;
}

