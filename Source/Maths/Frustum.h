#ifndef FRUSTUM_H_INCLUDED
#define FRUSTUM_H_INCLUDED

#include <array>

#include "glm.h"

class AABB;

struct Plane
{
    float distanceToPoint(const glm::vec3& point) const ;

    float distanceToOrigin;
    glm::vec3 normal;
};

class ViewFrustum
{
    public:
        void update(const glm::mat4& projViewMatrix) ;

        bool isBoxInFrustum(const AABB& box) const ;

    private:
        std::array<Plane, 6> m_planes;
};

#endif // FRUSTUM_H_INCLUDED
