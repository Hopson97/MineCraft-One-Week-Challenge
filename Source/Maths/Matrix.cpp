#include "Matrix.h"

#include "../Camera.h"
#include "../Entity.h"

glm::mat4 makeModelMatrix(const Entity& entity)
{
    glm::mat4 matrix;

    matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), {0, 0, 1});

    matrix = glm::translate(matrix, entity.position);

    return matrix;
}

glm::mat4 makeViewMatrix(const Camera& camera)
{
    glm::mat4 matrix;

    matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), {0, 0, 1});

    matrix = glm::translate(matrix, camera.position);

    return matrix;
}

glm::mat4 makeProjectionMatrix(float fov)
{
    return glm::perspective(glm::radians(fov), 1280.0f / 720.0f, 0.1f, 1000.0f);
}
