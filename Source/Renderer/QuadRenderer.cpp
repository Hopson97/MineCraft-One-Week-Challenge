#include "QuadRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Maths/Matrix.h"

QuadRenderer::QuadRenderer()
{
    //m_basicTexture.loadFromFile("test");

    m_quadModel.addData({
    {
        -0,  1, 0,
         1,  1, 0,
         1, -0, 0,
        -0, -0, 0,
    },
    {
        0, 1,
        1, 1,
        1, 0,
        0, 0,
    },
    {
        0, 1, 2,
        2, 3, 0
    }});
}

void QuadRenderer::add(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void QuadRenderer::render(const Camera& camera, Config* conf)
{
    if (m_quads.empty())
    {
        return;
    }

    m_shader.useProgram();
    m_shader.loadGamma(conf->gamma);
    m_shader.loadContrast(conf->contrast);
    m_shader.loadBrightness(conf->brightness);
    m_shader.loadPostProcess(conf->postProcess);
    m_shader.loadResolution(glm::vec2(conf->windowX, conf->windowY));
    
    m_quadModel.bindVAO();
    //m_basicTexture.bindTexture();

    m_shader.loadProjectionViewMatrix(glm::ortho(0, 1, 0, 1, 0, 1));

    for (auto& quad : m_quads)
    {
        m_shader.loadModelMatrix(glm::mat4());
        GL::drawElements(m_quadModel.getIndicesCount());
    }

    m_quads.clear();
}

