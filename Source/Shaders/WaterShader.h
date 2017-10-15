#ifndef WATERSHADER_H_INCLUDED
#define WATERSHADER_H_INCLUDED

#include "BasicShader.h"

class WaterShader : public BasicShader
{
    public:
        WaterShader();
        void loadTime (const float& time);
        void loadLighting(float light);
        void loadDTime(float time);
    private:
        void getUniforms() override;
        GLuint m_time;
        GLuint lighting;
        GLuint dtime;
};

#endif // WATERSHADER_H_INCLUDED
