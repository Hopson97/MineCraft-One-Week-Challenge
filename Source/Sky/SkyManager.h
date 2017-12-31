#ifndef SKY_MANAGER_H
#define SKY_MANAGER_H

#include "../Tick/TickObject.h"
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include "../Camera.h"
#include "../Model.h"
#include "../Shaders/SunShader.h"
#include "../Texture/BasicTexture.h"
#include "ProcSky.h"
#include "Cloud.h"
#include "../GlobalInfo.h"
class Camera;

class SkyManager : public TickObject
{
    public:
        SkyManager();

        void TickUpdate(unsigned int tickTime);
        void Update(glm::vec3 playerPosition);

        void setTime(unsigned int time);
        unsigned int getTime();

        void render(const Camera& camera);

    private:
        unsigned int dayTime;

        unsigned int m_prevTime; //Ticks can skip around sometimes so...
        glm::vec3 playerPos;
        glm::mat4 transformMatrix;

        Model m_SunModel;
        Model m_MoonModel;
        SunShader m_shader;

        BasicTexture sun;
        BasicTexture moon;

        ProcSky skyBox;
        Clouds clouds;
};

#endif
