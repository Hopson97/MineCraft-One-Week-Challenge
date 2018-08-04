#ifndef SKYBOXRENDERER_H_INCLUDED
#define SKYBOXRENDERER_H_INCLUDED

#include "../Shaders/SkyboxShader.h"
#include "../Texture/CubeTexture.h"
#include "../Model.h"

class Camera;

class SkyboxRenderer
{
    public:
        SkyboxRenderer();

        void render(const Camera& camera);

    private:
        Model           m_skyCube;
        SkyboxShader    m_shader;
        CubeTexture     m_cubeTexture;
};

#endif // SKYBOXRENDERER_H_INCLUDED
