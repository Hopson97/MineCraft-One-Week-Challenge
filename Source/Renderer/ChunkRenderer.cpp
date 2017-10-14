#include "ChunkRenderer.h"

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Block/BlockDatabase.h"

#include "../Camera.h"
#include "../Sky/SkyManager.h"

#include <iostream>

void ChunkRenderer::add(const ChunkMesh& mesh)
{
    m_chunks.push_back(&mesh.getModel().getRenderInfo());
}

void ChunkRenderer::render(const Camera& camera, Config* conf)
{
    if (m_chunks.empty())
    {
        return;
    }

    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);

    m_shader.useProgram();
    BlockDatabase::get().textureAtlas.bindTexture();

    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
    m_shader.loadLighting(g_info.lighting);

    for (auto mesh : m_chunks)
    {
        GL::bindVAO(mesh->vao);
        GL::drawElements(mesh->indicesCount);
    }

    m_chunks.clear();
}
