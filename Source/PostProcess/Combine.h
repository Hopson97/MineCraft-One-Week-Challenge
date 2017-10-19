#ifndef COMBINE_H
#define COMBINE_H

#include "../Shaders/BasicShader.h"

class CombineShader : public BasicShader{
public:
    CombineShader();

    void loadTex(GLuint t1);
    void loadTex2(GLuint t2);
private:
    void getUniforms() override;
    GLuint t1;
    GLuint t2;
};

#endif