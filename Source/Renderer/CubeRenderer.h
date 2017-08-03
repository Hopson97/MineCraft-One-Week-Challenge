#ifndef CUBERENDERER_H_INCLUDED
#define CUBERENDERER_H_INCLUDED

#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"
#include "../Texture/TextureAtlas.h"

class Camera;
struct Entity;

class CubeRenderer
{
    public:
        CubeRenderer();

        void add(const Entity& entity);

        void render(const Camera& camera);

    private:
        std::vector<const Entity*> m_cubes;

        Model m_cubeModel;
        BasicShader m_shader;
        BasicTexture m_basicTexture;

        TextureAtlas m_atlasTest;
};

#endif // CUBERENDERER_H_INCLUDED
