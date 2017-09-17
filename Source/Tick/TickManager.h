#ifndef TICK_MANAGER_H
#define TICK_MANAGER_H

#include "TickObject.h"
#include <vector>

class TickManager{
public:
    TickManager();

    void add(TickObject* tick);
    void run();

    int getTickTime();

private:
    std::vector<TickObject*> m_tickObjects;
    int m_tickTime;
};

#endif