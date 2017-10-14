#ifndef PROC_SKY_SHADER_H
#define PROC_SKY_SHADER_H

#include "BasicShader.h"

class ProcSkyShader : public BasicShader{
public:
    ProcSkyShader();
    void loadTime(float ticks);
    void loadViewMatrix         (glm::mat4 viewMatrix);
    void loadProjectionMatrix   (const glm::mat4& proj);

private:
    void getUniforms() override;
    GLuint m_day;
    GLuint m_locationProjection;
    GLuint m_locationView;
};

#endif