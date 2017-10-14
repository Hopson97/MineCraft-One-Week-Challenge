#include "Cloud.h"
#include <vector>
#include "SkyManager.h"
#include "../Application.h"

Clouds::Clouds():cloud("clouds"){
    std::vector<GLfloat> mvertexCoords
    {
            -2048,  128, 2048,
             2048,  128, 2048,
             2048,  128, -2048,
            -2048,  128, -2048
        };

    std::vector<GLfloat> mtextureCoords
        {
            0, 2,
            2, 2,
            2, 0,
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

    movement += g_info.deltaTime; //Move

    if(movement > 1024){
        movement = 0;
    }
    if(oldPos == glm::vec3(0.0f) && pos != glm::vec3(0.0f)){
        oldPos = pos;
    }

    if(abs(pos.x - oldPos.x) > 1024){
        oldPos.x = pos.x;
    }

    if(abs(pos.z - oldPos.z) > 1024){
        oldPos.z = pos.z;
    }

    m_shader.loadModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(oldPos.x, 0, oldPos.z + movement)));
    m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
    m_shader.loadLighting(g_info.lighting);

    GL::drawElements(m_cloud.getIndicesCount());
}
