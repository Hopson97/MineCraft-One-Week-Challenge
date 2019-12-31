#ifndef AABB_H_INCLUDED
#define AABB_H_INCLUDED

#include "../Maths/glm.h"

struct AABB {
    AABB(const glm::vec3 &dim)
        : dimensions(dim)
    {
    }

    void update(const glm::vec3 &location)
    {
        position = location;
    }

    glm::vec3 getVN(const glm::vec3 &normal) const
    {
        glm::vec3 res = position;

        if (normal.x < 0) {
            res.x += dimensions.x;
        }
        if (normal.y < 0) {
            res.y += dimensions.y;
        }
        if (normal.z < 0) {
            res.z += dimensions.z;
        }

        return res;
    }

    glm::vec3 getVP(const glm::vec3 &normal) const
    {
        glm::vec3 res = position;

        if (normal.x > 0) {
            res.x += dimensions.x;
        }
        if (normal.y > 0) {
            res.y += dimensions.y;
        }
        if (normal.z > 0) {
            res.z += dimensions.z;
        }

        return res;
    }

    glm::vec3 position;
    const glm::vec3 dimensions;
};

#endif // AABB_H_INCLUDED
