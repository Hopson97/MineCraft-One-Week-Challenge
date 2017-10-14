#ifndef TICK_MANAGER_H
#define TICK_MANAGER_H

#include "TickObject.h"
#include <vector>
#include <memory>
#include "../Context.h"

class TickManager
{
    public:
        TickManager();

        void add(std::shared_ptr<TickObject> tick);
        void run();

        int getTickTime();

    private:
        std::vector<std::shared_ptr<TickObject>> m_tickObjects;
        unsigned int m_tickTime;
};

#endif
