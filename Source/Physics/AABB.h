#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include "../Maths/glm.h"

struct AABB
{
    AABB(const glm::vec3& dim)
    :   dimensions  (dim)
    {

    }

    void update(const glm::vec3& location)
    {
        position = location;
    }

    glm::vec3 position;
    const glm::vec3 dimensions;
};

#endif // AABB_H_INCLUDED
