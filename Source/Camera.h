#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Maths/glm.h"

class Camera
{
    public:
        Camera();

        void update();

        const glm::mat4& getViewMatrix ()           const noexcept;
        const glm::mat4& getProjMatrix ()           const noexcept;
        const glm::mat4& getProjectionViewMatrix () const noexcept;

        const glm::vec3& getPosition() const noexcept;
        const glm::vec3& getRotation() const noexcept;

    private:
        glm::vec3 m_worldPosition;
        glm::vec3 m_rotation;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projViewMatrx;


};

#endif // CAMERA_H_INCLUDED
