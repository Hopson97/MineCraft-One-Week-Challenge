#include "World.h"

#include <future>
#include <iostream>

#include "../Camera.h"
#include "../Input/ToggleKey.h"
#include "../Maths/Vector2XZ.h"
#include "../Player/Player.h"
#include "../Renderer/RenderMaster.h"
#include "../Util/Random.h"

World::World(const Camera &camera, const Config &config, Player &player)
    : m_chunkManager(*this)
    , m_renderDistance(config.renderDistance)
{
    setSpawnPoint();
    player.position = m_playerSpawnPoint;

    for (int i = 0; i < 1; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        m_chunkLoadThreads.emplace_back([&]() { loadChunks(camera); });
    }
}

World::~World()
{
    m_isRunning = false;
    for (auto &thread : m_chunkLoadThreads) {
        thread.join();
    }
}

// world coords into chunk column coords
ChunkBlock World::getBlock(int x, int y, int z)
{
    auto bp = getBlockXZ(x, z);
    auto chunkPosition = getChunkXZ(x, z);

    return m_chunkManager.getChunk(chunkPosition.x, chunkPosition.z)
        .getBlock(bp.x, y, bp.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (y <= 0)
        return;

    auto bp = getBlockXZ(x, z);
    auto chunkPosition = getChunkXZ(x, z);

    m_chunkManager.getChunk(chunkPosition.x, chunkPosition.z)
        .setBlock(bp.x, y, bp.z, block);
}

// loads chunks
// make chunk meshes
void World::update(const Camera &camera)
{
    static ToggleKey key(sf::Keyboard::C);

    if (key.isKeyPressed()) {
        std::unique_lock<std::mutex> lock(m_mainMutex);
        m_chunkManager.deleteMeshes();
        m_loadDistance = 2;
    }

    for (auto &event : m_events) {
        event->handle(*this);
    }
    m_events.clear();

    updateChunks();
}

///@TODO
/// Optimize for chunkPositionU usage :thinking:
void World::loadChunks(const Camera &camera)
{
    while (m_isRunning) {
        bool isMeshMade = false;
        int cameraX = camera.position.x / CHUNK_SIZE;
        int cameraZ = camera.position.z / CHUNK_SIZE;

        for (int i = 0; i < m_loadDistance; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            int minX = std::max(cameraX - i, 0);
            int minZ = std::max(cameraZ - i, 0);
            int maxX = cameraX + i;
            int maxZ = cameraZ + i;

            for (int x = minX; x < maxX; ++x) {
                for (int z = minZ; z < maxZ; ++z) {
                    std::unique_lock<std::mutex> lock(m_mainMutex);
                    isMeshMade = m_chunkManager.makeMesh(x, z, camera);
                }
                // if (isMeshMade)
                //   break;
            }

            if (isMeshMade)
                break;
        }

        if (!isMeshMade) {
            m_loadDistance++;
        }
        if (m_loadDistance >= m_renderDistance) {
            m_loadDistance = 2;
        }
    }
}

void World::updateChunk(int blockX, int blockY, int blockZ)
{
    std::unique_lock<std::mutex> lock(m_mainMutex);

    auto addChunkToUpdateBatch = [&](const sf::Vector3i &key,
                                     ChunkSection &section) {
        m_chunkUpdates.emplace(key, &section);
    };

    auto chunkPosition = getChunkXZ(blockX, blockZ);
    auto chunkSectionY = blockY / CHUNK_SIZE;

    sf::Vector3i key(chunkPosition.x, chunkSectionY, chunkPosition.z);
    addChunkToUpdateBatch(
        key, m_chunkManager.getChunk(chunkPosition.x, chunkPosition.z)
                 .getSection(chunkSectionY));

    auto sectionBlockXZ = getBlockXZ(blockX, blockZ);
    auto sectionBlockY = blockY % CHUNK_SIZE;

    if (sectionBlockXZ.x == 0) {
        sf::Vector3i newKey(chunkPosition.x - 1, chunkSectionY,
                            chunkPosition.z);
        addChunkToUpdateBatch(
            newKey,
            m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }
    else if (sectionBlockXZ.x == CHUNK_SIZE - 1) {
        sf::Vector3i newKey(chunkPosition.x + 1, chunkSectionY,
                            chunkPosition.z);
        addChunkToUpdateBatch(
            newKey,
            m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }

    if (sectionBlockY == 0) {
        sf::Vector3i newKey(chunkPosition.x, chunkSectionY - 1,
                            chunkPosition.z);
        addChunkToUpdateBatch(
            newKey,
            m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }
    else if (sectionBlockY == CHUNK_SIZE - 1) {
        sf::Vector3i newKey(chunkPosition.x, chunkSectionY + 1,
                            chunkPosition.z);
        addChunkToUpdateBatch(
            newKey,
            m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }

    if (sectionBlockXZ.z == 0) {
        sf::Vector3i newKey(chunkPosition.x, chunkSectionY,
                            chunkPosition.z - 1);
        addChunkToUpdateBatch(
            newKey,
            m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }
    else if (sectionBlockXZ.z == CHUNK_SIZE - 1) {
        sf::Vector3i newKey(chunkPosition.x, chunkSectionY,
                            chunkPosition.z + 1);
        addChunkToUpdateBatch(
            newKey,
            m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
    }
}

void World::renderWorld(RenderMaster &renderer, const Camera &camera)
{
    std::unique_lock<std::mutex> lock(m_mainMutex);
    renderer.drawSky();

    auto &chunkMap = m_chunkManager.getChunks();
    for (auto itr = chunkMap.begin(); itr != chunkMap.end();) {
        Chunk &chunk = itr->second;

        int cameraX = camera.position.x;
        int cameraZ = camera.position.z;

        int minX = (cameraX / CHUNK_SIZE) - m_renderDistance;
        int minZ = (cameraZ / CHUNK_SIZE) - m_renderDistance;
        int maxX = (cameraX / CHUNK_SIZE) + m_renderDistance;
        int maxZ = (cameraZ / CHUNK_SIZE) + m_renderDistance;

        auto location = chunk.getLocation();

        if (minX > location.x || minZ > location.y || maxZ < location.y ||
            maxX < location.x) {
            itr = chunkMap.erase(itr);
            continue;
        }
        else {
            chunk.drawChunks(renderer, camera);
            itr++;
        }
    }
}

ChunkManager &World::getChunkManager()
{
    return m_chunkManager;
}

VectorXZ World::getBlockXZ(int x, int z)
{
    return {x % CHUNK_SIZE, z % CHUNK_SIZE};
}

VectorXZ World::getChunkXZ(int x, int z)
{
    return {x / CHUNK_SIZE, z / CHUNK_SIZE};
}

void World::updateChunks()
{
    std::unique_lock<std::mutex> lock(m_mainMutex);
    for (auto &c : m_chunkUpdates) {
        ChunkSection &s = *c.second;
        s.makeMesh();
    }
    m_chunkUpdates.clear();
}

void World::setSpawnPoint()
{
    sf::Clock timer;
    std::cout << "Searching for spawn...\n";
    int attempts = 0;
    int chunkX = -1;
    int chunkZ = -1;
    int blockX = 0;
    int blockZ = 0;
    int blockY = 0;

    auto h = m_chunkManager.getTerrainGenerator().getMinimumSpawnHeight();

    while (blockY <= h) {
        m_chunkManager.unloadChunk(chunkX, chunkZ);

        chunkX = RandomSingleton::get().intInRange(100, 200);
        chunkZ = RandomSingleton::get().intInRange(100, 200);
        blockX = RandomSingleton::get().intInRange(0, 15);
        blockZ = RandomSingleton::get().intInRange(0, 15);

        m_chunkManager.loadChunk(chunkX, chunkZ);
        blockY =
            m_chunkManager.getChunk(chunkX, chunkZ).getHeightAt(blockX, blockZ);
        attempts++;
    }

    int worldX = chunkX * CHUNK_SIZE + blockX;
    int worldZ = chunkZ * CHUNK_SIZE + blockZ;

    m_playerSpawnPoint = {worldX, blockY, worldZ};

    for (int x = worldX - 1; x <= worldX + 1; ++x) {
        for (int z = worldZ - 1; z < worldZ + 1; ++z) {
            std::unique_lock<std::mutex> lock(m_mainMutex);
            m_chunkManager.loadChunk(x, z);
        }
        // if (isMeshMade)
        //   break;
    }

    std::cout << "Spawn found! Attempts: " << attempts
              << " Time Taken: " << timer.getElapsedTime().asSeconds()
              << " seconds\n";
}
