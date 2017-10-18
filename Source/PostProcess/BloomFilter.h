#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/PostProcessShader.h"
#include "../Texture/BasicTexture.h"
#include "../Config.h"
#include "../ShaderData.h"
#include "../PostProcess/Framebuffer.h"
#include "GHShader.h"
#include "GVShader.h"
#include "MaskShader.h"

class Camera;

class BloomFilter{
public:
    BloomFilter();

    void add(const glm::vec3& position);
    void render(const Camera& camera, GLuint colTex);


    FrameBufferObject fbo;
private:

    std::vector<glm::vec3> m_quads;
    Model m_quadModel;

    GHShader gh_shader;
    GVShader gv_shader;
    //MaskShader mask_shader;
};

#endif