#include "ClassicOverWorldGenerator.h"

#include <functional>
#include <iostream>

#include "../../../Maths/GeneralMaths.h"
#include "../../../Util/Random.h"
#include "../../Chunk/Chunk.h"

#include "../Structures/TreeGenerator.h"

namespace {
const int seed = RandomSingleton::get().intInRange(424, 325322);
}

NoiseGenerator ClassicOverWorldGenerator::m_biomeNoiseGen(seed * 2);

ClassicOverWorldGenerator::ClassicOverWorldGenerator()
    : m_grassBiome(seed)
    , m_temperateForest(seed)
    , m_desertBiome(seed)
    , m_oceanBiome(seed)
    , m_lightForest(seed)
{
    setUpNoise();
}

void ClassicOverWorldGenerator::setUpNoise()
{
    std::cout << "Seed: " << seed << '\n';
    static bool noiseGen = false;
    if (!noiseGen) {
        std::cout << "making noise\n";
        noiseGen = true;

        NoiseParameters biomeParmams;
        biomeParmams.octaves = 5;
        biomeParmams.amplitude = 120;
        biomeParmams.smoothness = 1035;
        biomeParmams.heightOffset = 0;
        biomeParmams.roughness = 0.75;

        m_biomeNoiseGen.setParameters(biomeParmams);
    }
}

void ClassicOverWorldGenerator::generateTerrainFor(Chunk &chunk)
{
    m_pChunk = &chunk;

    auto location = chunk.getLocation();
    m_random.setSeed((location.x ^ location.y) << 2);

    getBiomeMap();
    getHeightMap();

    auto maxHeight = m_heightMap.getMaxValue();

    maxHeight = std::max(maxHeight, WATER_LEVEL);
    setBlocks(maxHeight);
}

int ClassicOverWorldGenerator::getMinimumSpawnHeight() const noexcept
{
    return WATER_LEVEL;
}

void ClassicOverWorldGenerator::getHeightIn(int xMin, int zMin, int xMax,
                                            int zMax)
{

    auto getHeightAt = [&](int x, int z) {
        const Biome &biome = getBiome(x, z);

        return biome.getHeight(x, z, m_pChunk->getLocation().x,
                               m_pChunk->getLocation().y);
    };

    float bottomLeft = static_cast<float>(getHeightAt(xMin, zMin));
    float bottomRight = static_cast<float>(getHeightAt(xMax, zMin));
    float topLeft = static_cast<float>(getHeightAt(xMin, zMax));
    float topRight = static_cast<float>(getHeightAt(xMax, zMax));

    for (int x = xMin; x < xMax; ++x)
        for (int z = zMin; z < zMax; ++z) {
            if (x == CHUNK_SIZE)
                continue;
            if (z == CHUNK_SIZE)
                continue;

            float h = smoothInterpolation(
                bottomLeft, topLeft, bottomRight, topRight,
                static_cast<float>(xMin), static_cast<float>(xMax),
                static_cast<float>(zMin), static_cast<float>(zMax),
                static_cast<float>(x), static_cast<float>(z));

            m_heightMap.get(x, z) = static_cast<int>(h);
        }
}

void ClassicOverWorldGenerator::getHeightMap()
{
    constexpr static auto HALF_CHUNK = CHUNK_SIZE / 2;
    constexpr static auto CHUNK = CHUNK_SIZE;

    getHeightIn(0, 0, HALF_CHUNK, HALF_CHUNK);
    getHeightIn(HALF_CHUNK, 0, CHUNK, HALF_CHUNK);
    getHeightIn(0, HALF_CHUNK, HALF_CHUNK, CHUNK);
    getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK, CHUNK);
}

void ClassicOverWorldGenerator::getBiomeMap()
{
    auto location = m_pChunk->getLocation();

    for (int x = 0; x < CHUNK_SIZE + 1; x++)
        for (int z = 0; z < CHUNK_SIZE + 1; z++) {
            double h = m_biomeNoiseGen.getHeight(x, z, location.x + 10,
                                                 location.y + 10);
            m_biomeMap.get(x, z) = static_cast<int>(h);
        }
}

void ClassicOverWorldGenerator::setBlocks(int maxHeight)
{
    std::vector<sf::Vector3i> trees;
    std::vector<sf::Vector3i> plants;

    for (int y = 0; y < maxHeight + 1; y++)
        for (int x = 0; x < CHUNK_SIZE; x++)
            for (int z = 0; z < CHUNK_SIZE; z++) {
                int height = m_heightMap.get(x, z);
                auto &biome = getBiome(x, z);

                if (y > height) {
                    if (y <= WATER_LEVEL) {
                        m_pChunk->setBlock(x, y, z, BlockId::Water);
                    }
                    continue;
                }
                else if (y == height) {
                    if (y >= WATER_LEVEL) {
                        if (y < WATER_LEVEL + 4) {
                            m_pChunk->setBlock(x, y, z,
                                               biome.getBeachBlock(m_random));
                            continue;
                        }

                        if (m_random.intInRange(0, biome.getTreeFrequency()) ==
                            5) {
                            trees.emplace_back(x, y + 1, z);
                        }
                        if (m_random.intInRange(0, biome.getPlantFrequency()) ==
                            5) {
                            plants.emplace_back(x, y + 1, z);
                        }
                        m_pChunk->setBlock(
                            x, y, z, getBiome(x, z).getTopBlock(m_random));
                    }
                    else {
                        m_pChunk->setBlock(x, y, z,
                                           biome.getUnderWaterBlock(m_random));
                    }
                }
                else if (y > height - 3) {
                    m_pChunk->setBlock(x, y, z, BlockId::Dirt);
                }
                else {
                    m_pChunk->setBlock(x, y, z, BlockId::Stone);
                }
            }

    for (auto &plant : plants) {
        int x = plant.x;
        int z = plant.z;

        auto block = getBiome(x, z).getPlant(m_random);
        m_pChunk->setBlock(x, plant.y, z, block);
    }

    for (auto &tree : trees) {
        int x = tree.x;
        int z = tree.z;

        getBiome(x, z).makeTree(m_random, *m_pChunk, x, tree.y, z);
    }
}

const Biome &ClassicOverWorldGenerator::getBiome(int x, int z) const
{
    int biomeValue = m_biomeMap.get(x, z);

    if (biomeValue > 160) {
        return m_oceanBiome;
    }
    else if (biomeValue > 150) {
        return m_grassBiome;
    }
    else if (biomeValue > 130) {
        return m_lightForest;
    }
    else if (biomeValue > 120) {
        return m_temperateForest;
    }
    else if (biomeValue > 110) {
        return m_lightForest;
    }
    else if (biomeValue > 100) {
        return m_grassBiome;
    }
    else {
        return m_desertBiome;
    }
}
