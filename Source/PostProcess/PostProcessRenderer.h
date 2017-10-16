#ifndef POST_PROCESS_RENDERER_H
#define POST_PROCESS_RENDERER_H


#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/PostProcessShader.h"
#include "../Texture/BasicTexture.h"
#include "../Config.h"
#include "../ShaderData.h"

class Camera;

class PostProcessRender
{
    public:
        PostProcessRender();
        
        void add(const glm::vec3& position);
        void render(const Camera& camera, Config* conf);

    private:
        std::vector<glm::vec3> m_quads;

        Model m_quadModel;
        PostProcessShader m_shader;
};

#endif