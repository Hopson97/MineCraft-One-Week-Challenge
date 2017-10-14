#include "Cloud.h"
#include <vector>
#include "SkyManager.h"
#include "../Application.h"

Clouds::Clouds():cloud("clouds"){
    std::vector<GLfloat> mvertexCoords
    {
            -1024,  128, 1024,
             1024,  128, 1024,
             1024,  128, -1024,
            -1024,  128, -1024
        };

    std::vector<GLfloat> mtextureCoords
        {
            0, 1,
            1, 1,
            1, 0,
            0, 0,
        };

    std::vector<GLuint> mindexCoords
    {
        0, 1, 2,
        2, 3, 0
    };

    m_cloud.addData({mvertexCoords, mtextureCoords, mindexCoords});

}

void Clouds::Render(const Camera& camera, glm::vec3 pos){
    m_shader.useProgram();
    m_cloud.bindVAO();
    cloud.bindTexture();

    movement += g_deltaTime; //Move

    if(movement > 256){
        movement = 256;
    }

    m_shader.loadModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, 0, pos.z + movement)));
    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
    m_shader.loadLighting(g_light);

    //GL::drawElements(m_cloud.getIndicesCount());
}
