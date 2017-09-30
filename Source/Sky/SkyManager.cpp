#include "SkyManager.h"
#include <iostream>

#define degreesToRadians(x) x*(3.141592f/180.0f)

SkyManager::SkyManager()
: sun("Sun"), moon("Moon")
{
    dayTime = 0; //Dawn
    m_prevTime = 0; //Time now

    std::vector<GLfloat> svertexCoords
    { 
            -70,  70, 400,
             70,  70, 400,
             70, -70, 400,
            -70, -70, 400
        };

    std::vector<GLfloat> stextureCoords
        {
            0, 1,
            1, 1,
            1, 0,
            0, 0,
        };

    std::vector<GLuint> sindexCoords
    {
        0, 1, 2,
        2, 3, 0
    };

    m_SunModel.addData({svertexCoords, stextureCoords, sindexCoords});

    std::vector<GLfloat> mvertexCoords
    { 
            -70,  70, -400,
             70,  70, -400,
             70, -70, -400,
            -70, -70, -400
        };

    std::vector<GLfloat> mtextureCoords
        {
            0, 1,
            1, 1,
            1, 0,
            0, 0,
        };

    std::vector<GLuint> mindexCoords
    {
        0, 1, 2,
        2, 3, 0
    };

    m_MoonModel.addData({mvertexCoords, mtextureCoords, mindexCoords});

}

void SkyManager::TickUpdate(unsigned int tickTime){
    //Day Time Management
    dayTime += tickTime - m_prevTime;
    m_prevTime = tickTime;

    if(dayTime > 23999){
        dayTime = 0;
    }

    //Update Sun/Moon matrix
    transformMatrix = glm::translate(glm::mat4(1.0f), playerPos);
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

void SkyManager::render(const Camera& camera){
    
    glEnable(GL_BLEND);  
    m_shader.useProgram();
    m_SunModel.bindVAO();
    sun.bindTexture();

    m_shader.loadModelMatrix(transformMatrix);
    m_shader.loadProjectionViewMatrix   (camera.getProjectionViewMatrix());
    m_shader.loadTime((float)dayTime/24000);

    GL::drawElements(m_SunModel.getIndicesCount());

    m_shader.useProgram();
    m_MoonModel.bindVAO();
    moon.bindTexture();

    m_shader.loadModelMatrix(transformMatrix);
    m_shader.loadProjectionViewMatrix   (camera.getProjectionViewMatrix());
    m_shader.loadTime((float)dayTime/24000);

    GL::drawElements(m_MoonModel.getIndicesCount());
    glDisable(GL_BLEND);
}