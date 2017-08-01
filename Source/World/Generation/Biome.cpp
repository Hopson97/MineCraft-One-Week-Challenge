#include "Biome.h"

Biome::Biome(const NoiseParameters& parameters, int treeFreq, int seed) noexcept
:   m_heightGenerator   (seed)
,   m_treeFreq          (treeFreq)
{
    m_heightGenerator.setParameters(parameters);
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const noexcept
{
    return m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int Biome::getTreeFrequency() const noexcept
{
    return m_treeFreq;
}

