#ifndef PROC_SKY_H
#define PROC_SKY_H

#include "../Shaders/ProcSkyShader.h"
#include "../Model.h"
#include "../Camera.h"


class Camera;

class ProcSky
{
public:
    ProcSky();

    void Render(const Camera& camera);
private:
    ProcSkyShader m_shader;
    Model m_skybox;
};

#endif