#ifndef WATERSHADER_H_INCLUDED
#define WATERSHADER_H_INCLUDED

#include "BasicShader.h"

/// @brief Shader affecting water blocks specifically.
class WaterShader : public BasicShader {
  public:
    WaterShader();
    void loadTime(const float &time);

  private:
    void getUniforms() override;
    GLuint m_time;
};

#endif // WATERSHADER_H_INCLUDED
