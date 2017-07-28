#ifndef CUBERENDERER_H_INCLUDED
#define CUBERENDERER_H_INCLUDED

#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"

class Camera;

class CubeRenderer
{
    public:
        CubeRenderer();

        void add(const glm::vec3& position);

        void render(const Camera& camera);

    private:
        std::vector<glm::vec3> m_quads;

        Model m_cubeModel;
        BasicShader m_shader;
        BasicTexture m_basicTexture;
};

#endif // CUBERENDERER_H_INCLUDED
