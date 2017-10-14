#ifndef TICK_MANAGER_H
#define TICK_MANAGER_H

#include "TickObject.h"
#include <vector>
#include "../Context.h"

class TickManager
{
    public:
        TickManager();

        void add(TickObject* tick);
        void run();

        int getTickTime();

    private:
        std::vector<TickObject*> m_tickObjects;
        unsigned int m_tickTime;
};

#endif
