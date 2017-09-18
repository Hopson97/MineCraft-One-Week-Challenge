#include "SkyManager.h"

SkyManager::SkyManager(){
    dayTime = 0; //Dawn
    m_prevTime = 0; //Time now
}

void SkyManager::TickUpdate(unsigned int tickTime){
    //Day Time Management
    dayTime += tickTime - m_prevTime;
    m_prevTime = tickTime;

    if(dayTime > 23999){
        dayTime = 0;
    }

    //Update Sun/Moon models


}

void SkyManager::setTime(unsigned int tickTime){
    dayTime = tickTime;
}

unsigned int SkyManager::getTime(){
    return dayTime;
}

void SkyManager::Update(glm::vec3 position){
    playerPos = position;
}