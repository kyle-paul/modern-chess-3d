#pragma once
#include "Core/Render/CameraConfig.h"
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionViewMatrix();

    CameraSpec m_Camspec;
      
private:
};