#include "Camera.h"

#include "Maths/Matrix.h"

Camera::Camera()
{
    m_projectionMatrix = makeProjectionMatrix(90);

    m_worldPosition = {0, 0, -5};
    m_rotation      = {0, 0, 0};
}

void Camera::update()
{
    m_viewMatrix = makeViewMatrix(*this);
    m_projViewMatrx = m_projectionMatrix * m_viewMatrix;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
    return m_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix() const noexcept
{
    return m_projectionMatrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const noexcept
{
    return m_projViewMatrx;
}

const glm::vec3& Camera::getPosition() const noexcept
{
    return m_worldPosition;
}

const glm::vec3& Camera::getRotation() const noexcept
{
    return m_rotation;
}

