#ifndef CHUNKMANAGER_H_INCLUDED
#define CHUNKMANAGER_H_INCLUDED

#include <functional>
#include <memory>
#include <unordered_map>

#include "../../Maths/Vector2XZ.h"
#include "../Generation/Terrain/TerrainGenerator.h"
#include "Chunk.h"

class World;

using ChunkMap = std::unordered_map<VectorXZ, Chunk>;

class ChunkManager {
  public:
    ChunkManager(World &world);

    Chunk &getChunk(int x, int z);
    ChunkMap &getChunks();

    bool makeMesh(int x, int z, const Camera &camera);

    bool chunkLoadedAt(int x, int z) const;
    bool chunkExistsAt(int x, int z) const;

    void loadChunk(int x, int z);
    void unloadChunk(int x, int z);

    void deleteMeshes();

    const TerrainGenerator &getTerrainGenerator() const noexcept;

  private:
    ChunkMap m_chunks;
    std::unique_ptr<TerrainGenerator> m_terrainGenerator;

    World *m_world;
};

#endif // CHUNKMANAGER_H_INCLUDED
