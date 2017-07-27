#include "Matrix.h"

#include "../Camera.h"

glm::mat4 makeViewMatrix(const Camera& camera)
{
    glm::mat4 matrix;

    auto& rot = camera.getRotation();
    matrix = glm::rotate(matrix, glm::radians(rot.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(rot.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(rot.z), {0, 0, 1});

    matrix = glm::translate(matrix, camera.getPosition());

    return matrix;
}

glm::mat4 makeProjectionMatrix(float fov)
{
    return glm::perspective(fov, 1280.0f / 720.0f, 0.1f, 1000.0f);
}
