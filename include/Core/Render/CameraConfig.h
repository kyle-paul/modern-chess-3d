#pragma once
#include <glm/glm.hpp>

struct CameraSpec
{
    // Perspective camera
    float FOV = 45.0f;
    float Aspect;
    float NearClip = 0.1f;
    float FarClip = 100.0f;

    // View matrix 
    glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.5f, 20.0f);
    glm::vec3 m_CameraRot = glm::vec3(-1.0f, 0.0f, 0.0f);

    glm::vec3 OX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 OY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 OZ = glm::vec3(0.0f, 0.0f, 1.0f);
};