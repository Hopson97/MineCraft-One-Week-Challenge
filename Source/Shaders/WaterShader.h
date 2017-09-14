#ifndef WATERSHADER_H_INCLUDED
#define WATERSHADER_H_INCLUDED

#include "BasicShader.h"

class WaterShader : public BasicShader
{
    public:
        WaterShader();

        void loadBrightness (const float& brightness);
        void loadContrast (const float& contrast);
        void loadGamma (const float& gamma);
        void loadTime (const float& time);
    private:
        void getUniforms() override;

        GLuint m_brightness;
        GLuint m_contrast;
        GLuint m_gamma;
        GLuint m_time;
};

#endif // WATERSHADER_H_INCLUDED
