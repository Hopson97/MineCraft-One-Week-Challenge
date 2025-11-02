#ifndef SKYBOXSHADER_H_INCLUDED
#define SKYBOXSHADER_H_INCLUDED

#include "Shader.h"

class SkyboxShader : public Shader {
  public:
    SkyboxShader();

    void loadViewMatrix(glm::mat4 viewMatrix);
    void loadProjectionMatrix(const glm::mat4 &proj);

  private:

    GLuint m_locationProjection;
    GLuint m_locationView;
};

#endif // SKYBOXSHADER_H_INCLUDED
