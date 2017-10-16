#ifndef BASIC_FILTER_H
#define BASIC_FILTER_H

#include "../Shaders/BasicShader.h"

#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Texture/BasicTexture.h"
#include "../Config.h"
#include "../ShaderData.h"

class Camera;


class BaseFilter: NonCopyable{
public:
    BaseFilter(int framebufferX, int framebufferY);

    GLuint getOutputTexture();
    GLuint getDepthTexture();

    virtual void render(const Camera& camera, GLuint colTex, GLuint depTex)=0;
         
    void add(const glm::vec3& position);

    std::vector<glm::vec3> m_quads;
    Model m_quadModel;
    GLuint m_fbo;

    GLuint m_colTex;
    GLuint m_depTex;

};


#endif