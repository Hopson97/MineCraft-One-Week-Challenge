#ifndef TICK_OBJECT_H
#define TICK_OBJECT_H

class TickObject{
public:
    virtual void TickUpdate(unsigned int tickTime) = 0;
};

#endif