#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"

#include "Event/IWorldEvent.h"

class RenderMaster;
class Camera;
class Entity;

class World
{
    public:
        World(const Camera& camera);

        ChunkBlock  getBlock    (int x, int y, int z);
        void        setBlock    (int x, int y, int z, ChunkBlock block);

        void update(const Camera& camera);
        void updateChunk(int blockX, int blockY, int blockZ);

        void renderWorld(RenderMaster& master, const Camera& camera);

        ChunkManager& getChunkManager();

        static VectorXZ getBlockXZ(int x, int z);
        static VectorXZ getChunkXZ(int x, int z);

        void collisionTest(Entity& entity);

        template<typename T, typename... Args>
        void addEvent(Args&&... args)
        {
            m_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        }

    private:
        void loadChunks     (const Camera& camera);
        void updateChunks   ();

        ChunkManager m_chunkManager;

        std::vector<std::unique_ptr<IWorldEvent>> m_events;
        std::unordered_map<sf::Vector3i, ChunkSection*> m_chunkUpdates;



        int m_loadDistance = 2;
};

#endif // WORLD_H_INCLUDED
