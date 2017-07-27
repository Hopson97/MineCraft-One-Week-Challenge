#include "QuadRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Maths/Matrix.h"

QuadRenderer::QuadRenderer()
{
    m_basicTexture.loadFromFile("test");

    m_quadModel.addData(
    {
        -0.5,  0.5, 0,
         0.5,  0.5, 0,
         0.5, -0.5, 0,
        -0.5, -0.5, 0,
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
    });
}

void QuadRenderer::add(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void QuadRenderer::renderQuads(const Camera& camera)
{
    m_shader.useProgram();
    m_quadModel.bindVAO();
    m_basicTexture.bindTexture();

    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

    for (auto& quad : m_quads)
    {
         m_shader.loadModelMatrix(makeModelMatrix({quad, {0, 0, 0}}));

         glDrawElements(GL_TRIANGLES, m_quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    m_quads.clear();
}

