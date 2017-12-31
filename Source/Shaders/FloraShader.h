#ifndef FLORASHADER_H_INCLUDED
#define FLORASHADER_H_INCLUDED

#include "BasicShader.h"

class FloraShader : public BasicShader
{
    public:
        FloraShader();
        void loadTime (const float& time);
        void loadLight (float lighting);
        void loadDTime (float time);
    private:
        void getUniforms() override;
        GLuint m_time;
        GLuint m_light;
        GLuint dtime;
};


#endif // FLORASHADER_H_INCLUDED
