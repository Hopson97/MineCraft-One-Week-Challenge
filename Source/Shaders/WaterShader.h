#ifndef WATERSHADER_H_INCLUDED
#define WATERSHADER_H_INCLUDED

#include "BasicShader.h"

class WaterShader : public BasicShader
{
    public:
        WaterShader();

        void addTime(float time);

    private:
        void getUniforms() override;

        GLuint m_locationTime;
};

#endif // WATERSHADER_H_INCLUDED
