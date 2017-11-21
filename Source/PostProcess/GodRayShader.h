#ifndef GOD_RAYS_SHADER_H
#define GOD_RAYS_SHADER_H

#include "../Shaders/BasicShader.h"

class GodRayShader : public BasicShader{
public:
    GodRayShader();
    void loadRes(glm::vec2 res);
    void loadTime(float time);
    void loadCPV(glm::mat4 m);
    void loadMM(glm::mat4 m);
private:
    void getUniforms() override;
    GLuint m_res;
    GLuint m_time;
    GLuint m_camPV;
    GLuint m_mm;
};

#endif