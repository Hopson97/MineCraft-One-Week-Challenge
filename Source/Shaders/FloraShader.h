#ifndef FLORASHADER_H_INCLUDED
#define FLORASHADER_H_INCLUDED

#include "BasicShader.h"

class FloraShader : public BasicShader {
  public:
    FloraShader();
    void loadTime(const float &time);

  private:
    void getUniforms() override;
    GLuint m_time;
};

#endif // FLORASHADER_H_INCLUDED
