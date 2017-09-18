#ifndef SKY_MANAGER_H
#define SKY_MANAGER_H

#include "../Tick/TickObject.h"
#include <glm/glm.hpp>
#include "../Camera.h"

class Camera;

class SkyManager : public TickObject{
public:
    SkyManager();
    
    void TickUpdate(unsigned int tickTime);
    void Update(glm::vec3 playerPosition);

    void setTime(unsigned int time);
    unsigned int getTime();

private:
    unsigned int dayTime;

    unsigned int m_prevTime; //Ticks can skip around sometimes so...
    glm::vec3 playerPos;
};

#endif