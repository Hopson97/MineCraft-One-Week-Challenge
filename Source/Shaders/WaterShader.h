#ifndef WATERSHADER_H_INCLUDED
#define WATERSHADER_H_INCLUDED

#include "BasicShader.h"

class WaterShader : public BasicShader
{
    public:
        WaterShader();
        void loadTime (const float& time);
        void loadLighting(float light);
    private:
        void getUniforms() override;
        GLuint m_time;
        GLuint lighting;
};

#endif // WATERSHADER_H_INCLUDED
