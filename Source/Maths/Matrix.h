#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "glm.h"

class Camera;

glm::mat4 makeViewMatrix(const Camera& camera);

glm::mat4 makeProjectionMatrix(float fov);

#endif // MATRIX_H_INCLUDED
