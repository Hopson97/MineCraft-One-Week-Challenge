#ifndef MOTION_BLUR_H
#define MOTION_BLUR_H

#include "../Shaders/BasicShader.h"

class MotionBlur : public BasicShader{
public:
    MotionBlur();

    void loadT1();
    void loadT2();
    void loadPrevProj(glm::mat4 prev);
    void loadCurrProj(glm::mat4 curr);

private:
    void getUniforms();
    GLuint t1, t2, m_prev, m_curr;
};

#endif