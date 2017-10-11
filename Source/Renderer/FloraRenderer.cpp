#include "FloraRenderer.h"

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Block/BlockDatabase.h"
#include "../Application.h"
#include "../Camera.h"

#include <iostream>

void FloraRenderer::add(const ChunkMesh& mesh)
{
    m_chunks.push_back(&mesh);
}

void FloraRenderer::render(const Camera& camera, Config* conf)
{
    if (m_chunks.empty())
    {
        return;
    }

    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    m_shader.useProgram();

    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
    m_shader.loadTime(g_timeElapsed);

    for (const auto& mesh : m_chunks)
    {
        const ChunkMesh& m = *mesh;

        m.getModel().bindVAO();
        GL::drawElements(m.getModel().getIndicesCount());
    }

    m_chunks.clear();
}
