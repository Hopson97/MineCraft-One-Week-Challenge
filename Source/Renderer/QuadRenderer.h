#ifndef QUADRENDERER_H_INCLUDED
#define QUADRENDERER_H_INCLUDED

#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"

class Camera;

class QuadRenderer
{
    public:
        QuadRenderer();

        void add(const glm::vec3& position);

        void renderQuads(const Camera& camera);

    private:
        std::vector<glm::vec3> m_quads;

        Model m_quadModel;
        BasicShader m_shader;
        BasicTexture m_basicTexture;
};

#endif // QUADRENDERER_H_INCLUDED
