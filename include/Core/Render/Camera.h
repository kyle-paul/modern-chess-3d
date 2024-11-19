#pragma once
#include "Core/Render/CameraConfig.h"
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    const glm::mat4 GetProjectionMatrix() const;
    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionViewMatrix() const;
    const glm::vec3 InterpolateWhite(float t) const;
    const glm::vec3 InterpolateBlack(float t) const;

    CameraSpec m_Camspec;
      
private:
};