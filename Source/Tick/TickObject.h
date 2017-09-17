#ifndef TICK_OBJECT_H
#define TICK_OBJECT_H

class TickObject{
public:
    TickObject();
    
    virtual void TickUpdate() = 0;
};

#endif