#include "CubeRenderer.h"

#include <iostream>

#include "../Camera.h"
#include "../Maths/Matrix.h"

CubeRenderer::CubeRenderer()
:   m_atlasTest ("DefaultPack")
{
    m_basicTexture.loadFromFile("test");


    std::vector<GLfloat> vertexCoords
    {
        //Back
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,

        //Front
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        //Right
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,

        //Left
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,

        //Top
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,

        //Bottom
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1.
    };

    auto top    = m_atlasTest.getTexture({0, 0});
    auto side   = m_atlasTest.getTexture({1, 0});
    auto bottom = m_atlasTest.getTexture({2, 0});

    std::vector<GLfloat> texCoords;
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), top.begin(),      top.end());
    texCoords.insert(texCoords.end(), bottom.begin(),   bottom.end());


    std::vector<GLuint> indices
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    m_cubeModel.addData({vertexCoords, texCoords, indices});
}

void CubeRenderer::add(const Entity& entity)
{
    m_cubes.push_back(&entity);
}

void CubeRenderer::render(const Camera& camera)
{
    if (m_cubes.empty())
    {
        return;
    }


    m_shader.useProgram();
    m_cubeModel.bindVAO();
    m_atlasTest.bindTexture();

    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

    for (auto& cube : m_cubes)
    {
        m_shader.loadModelMatrix(makeModelMatrix(*cube));
        GL::drawElements(m_cubeModel.getIndicesCount());
    }

    m_cubes.clear();
}

