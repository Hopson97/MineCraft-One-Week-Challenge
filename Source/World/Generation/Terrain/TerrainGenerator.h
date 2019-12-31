#ifndef TERRAINGENERATOR_H_INCLUDED
#define TERRAINGENERATOR_H_INCLUDED

class Chunk;

class TerrainGenerator {
  public:
    virtual void generateTerrainFor(Chunk &chunk) = 0;
    virtual int getMinimumSpawnHeight() const noexcept = 0;

    virtual ~TerrainGenerator() = default;
};

#endif // TERRAINGENERATOR_H_INCLUDED
