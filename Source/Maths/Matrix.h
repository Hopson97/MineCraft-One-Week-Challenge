#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "glm.h"

class Camera;

struct Entity;
struct Config;

glm::mat4 makeModelMatrix(const Entity &entity);
glm::mat4 makeViewMatrix(const Camera &camera);
glm::mat4 makeProjectionMatrix(const Config &config);

#endif // MATRIX_H_INCLUDED
