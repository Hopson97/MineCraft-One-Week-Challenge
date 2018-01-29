#include "ProcSky.h"
#include <vector>
#include "SkyManager.h"

ProcSky::ProcSky()
{
    GLfloat SIZE = 500;


    std::vector<GLfloat> vertexCoords =
        //Back
    {
        SIZE, -SIZE, -SIZE, 3,
        -SIZE, -SIZE, -SIZE, 0,
        -SIZE,  SIZE, -SIZE, 1,
        SIZE,  SIZE, -SIZE, 2,

        //Front
        -SIZE, -SIZE, SIZE, 4,
        SIZE, -SIZE, SIZE, 7,
        SIZE,  SIZE, SIZE, 5,
        -SIZE,  SIZE, SIZE, 6,

        //Right
        SIZE, -SIZE,  SIZE, 7,
        SIZE, -SIZE, -SIZE, 3,
        SIZE,  SIZE, -SIZE, 2,
        SIZE,  SIZE,  SIZE, 5,

        //Left
        -SIZE, -SIZE, -SIZE, 0,
        -SIZE, -SIZE,  SIZE, 4,
        -SIZE,  SIZE,  SIZE, 6,
        -SIZE,  SIZE, -SIZE, 1,

        //Top
        -SIZE, SIZE,  SIZE, 6,
        SIZE, SIZE,  SIZE, 5,
        SIZE, SIZE, -SIZE, 2,
        -SIZE, SIZE, -SIZE, 1,

        //Bottom
        -SIZE, -SIZE, -SIZE, 0,
        SIZE, -SIZE, -SIZE, 3,
        SIZE, -SIZE,  SIZE, 7,
        -SIZE, -SIZE,  SIZE, 4,
    };

    std::vector<GLuint> indices {
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

    m_skybox.genVAO();
    m_skybox.addVBO(4, vertexCoords);
    m_skybox.addEBO(indices);

}

void ProcSky::Render(const Camera& camera)
{
    m_shader.useProgram();
    m_skybox.bindVAO();

    m_shader.loadViewMatrix         (camera.getViewMatrix());
    m_shader.loadProjectionMatrix   (camera.getProjMatrix());
    m_shader.loadTime(g_info.dayTime);

    GL::drawElements(m_skybox.getIndicesCount());
}
