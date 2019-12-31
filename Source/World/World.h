#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "../Util/NonCopyable.h"
#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"

#include "Event/IWorldEvent.h"

#include "../Config.h"

class RenderMaster;
class Camera;
class Player;

struct Entity;

class World : public NonCopyable {
  public:
    World(const Camera &camera, const Config &config, Player &player);
    ~World();

    ChunkBlock getBlock(int x, int y, int z);
    void setBlock(int x, int y, int z, ChunkBlock block);

    void update(const Camera &camera);
    void updateChunk(int blockX, int blockY, int blockZ);

    void renderWorld(RenderMaster &master, const Camera &camera);

    ChunkManager &getChunkManager();

    static VectorXZ getBlockXZ(int x, int z);
    static VectorXZ getChunkXZ(int x, int z);

    void collisionTest(Entity &entity);

    template <typename T, typename... Args> void addEvent(Args &&... args)
    {
        m_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

  private:
    void loadChunks(const Camera &camera);
    void updateChunks();
    void setSpawnPoint();

    ChunkManager m_chunkManager;

    std::vector<std::unique_ptr<IWorldEvent>> m_events;
    std::unordered_map<sf::Vector3i, ChunkSection *> m_chunkUpdates;

    std::atomic<bool> m_isRunning{true};
    std::vector<std::thread> m_chunkLoadThreads;
    std::mutex m_mainMutex;
    std::mutex m_genMutex;

    int m_loadDistance = 2;
    const int m_renderDistance;

    glm::vec3 m_playerSpawnPoint;
};

#endif // WORLD_H_INCLUDED
