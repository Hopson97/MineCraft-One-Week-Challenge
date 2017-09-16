#include "ChunkRenderer.h"

#include "../World/Chunk/ChunkMesh.h"
#include "../World/Block/BlockDatabase.h"

#include "../Camera.h"

#include <iostream>

void ChunkRenderer::add(const ChunkMesh& mesh)
{
    m_chunks.push_back(&mesh);
}

void ChunkRenderer::render(const Camera& camera, Config* conf)
{
    if (m_chunks.empty())
    {
        return;
    }

    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);

    m_shader.useProgram(); 
    BlockDatabase::get().textureAtlas.bindTexture();

    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

    for (const ChunkMesh* mesh : m_chunks)
    {
        const ChunkMesh& m = *mesh;

        m.getModel().bindVAO();
        GL::drawElements(m.getModel().getIndicesCount());
    }

    m_chunks.clear();
}
