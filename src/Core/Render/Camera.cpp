#include "Core/Render/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

Camera::Camera()
{

}

Camera::~Camera()
{

}

const glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_Camspec.FOV), m_Camspec.Aspect, 
                            m_Camspec.NearClip, m_Camspec.FarClip);
}

const glm::mat4 Camera::GetViewMatrix() const
{
    return glm::mat4(
        m_Camspec.OX.x, m_Camspec.OY.x, m_Camspec.OZ.x, 0.0f,
        m_Camspec.OX.y, m_Camspec.OY.y, m_Camspec.OZ.y, 0.0f,
        m_Camspec.OX.z, m_Camspec.OY.z, m_Camspec.OZ.z, 0.0f,
        -m_Camspec.position.x, -m_Camspec.position.y, -m_Camspec.position.z, 1.0f
    ) * glm::toMat4(glm::quat(m_Camspec.rotation));
}

const glm::mat4 Camera::GetProjectionViewMatrix() const
{
    return GetProjectionMatrix() * GetViewMatrix();
}

const glm::vec3 Camera::InterpolateWhite() const
{
    return glm::lerp(m_Camspec.current, m_Camspec.desired, m_Camspec.time);
}

const glm::vec3 Camera::InterpolateBlack() const
{
    return glm::lerp(m_Camspec.desired, m_Camspec.current, m_Camspec.time - 1.0f);
}