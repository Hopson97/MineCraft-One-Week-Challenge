#ifndef QUADRENDERER_H_INCLUDED
#define QUADRENDERER_H_INCLUDED

#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/PostProcessShader.h"
#include "../Texture/BasicTexture.h"
#include "../Config.h"

class Camera;

class QuadRenderer
{
    public:
        QuadRenderer();

        void add(const glm::vec3& position);

        void render(const Camera& camera, Config* conf);

    private:
        std::vector<glm::vec3> m_quads;

        Model m_quadModel;
        PostProcessShader m_shader;
        BasicTexture m_basicTexture;
};

#endif // QUADRENDERER_H_INCLUDED
