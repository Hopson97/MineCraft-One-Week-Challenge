#include "SkyManager.h"
#include <iostream>

#define degreesToRadians(x) x*(3.141592f/180.0f)
float g_light;
float g_ticks;

//blend
float blend(float x, float y, float factor){
    return x + ((y-x) * factor);
}

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


    //Ambient light
    //0 = 6am
    //12000 = 6pm
    if(dayTime < 1500){ //6am - 9am sun gets brighter
        g_light = blend(0.6f, 1.0f, (float)dayTime / 1500); 
    }
    if(dayTime > 1500 && dayTime < 10500){ //9am - 3pm sun is brightest
        g_light = 1.0f;
    }
    if(dayTime > 10500 && dayTime < 12000){ //3pm - 6pm sun gets dimmer
        g_light = blend(1.0f, 0.6f,(float)((float)dayTime - 10500) / 1500);
    }
    if(dayTime > 12000 && dayTime < 13500){ //6pm - 9pm sun light fades
        g_light = blend(0.6f, 0.2f, (float)((float)dayTime - 12000)/ 1500);
    }
    if(dayTime > 13500 && dayTime < 22500){//9pm - 3am is night
        g_light = 0.2f;
    }
    if(dayTime > 22500 && dayTime < 24000){
        g_light = blend(0.2f, 0.6f, (float)((float)dayTime-22500) / 1500);
    }
    
    //Update Sun/Moon matrix
    transformMatrix = glm::translate(glm::mat4(1.0f), playerPos);

    g_ticks = dayTime;
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
    
    skyBox.Render(camera);
    glEnable(GL_BLEND);  
    m_shader.useProgram();
    m_SunModel.bindVAO();
    sun.bindTexture();

    m_shader.loadModelMatrix(transformMatrix);
    m_shader.loadProjectionViewMatrix   (camera.getProjectionViewMatrix());
    m_shader.loadTime(degreesToRadians(((float)dayTime/24000) * 360));

    GL::drawElements(m_SunModel.getIndicesCount());

    m_shader.useProgram();
    m_MoonModel.bindVAO();
    moon.bindTexture();

    m_shader.loadModelMatrix(transformMatrix);
    m_shader.loadProjectionViewMatrix   (camera.getProjectionViewMatrix());
    m_shader.loadTime(degreesToRadians(((float)dayTime/24000) * 360));

    GL::drawElements(m_MoonModel.getIndicesCount());
    glDisable(GL_BLEND);

}