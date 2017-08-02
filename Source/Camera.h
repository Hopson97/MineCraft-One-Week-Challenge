#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Maths/glm.h"
#include "Maths/Frustum.h"
#include "Entity.h"

class Camera : public Entity
{
    public:
        Camera();

        void update();
        void hookEntity(const Entity& entity);

        const glm::mat4& getViewMatrix ()           const ;
        const glm::mat4& getProjMatrix ()           const ;
        const glm::mat4& getProjectionViewMatrix () const ;

        const ViewFrustum& getFrustum() const ;

    private:
        const Entity* m_pEntity;

        ViewFrustum m_frustum;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projViewMatrx;


};

#endif // CAMERA_H_INCLUDED
