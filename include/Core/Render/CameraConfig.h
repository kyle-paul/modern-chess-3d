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
    glm::vec3 position = glm::vec3(0.0f, 0.6f, 20.0f);
    glm::vec3 rotation = glm::vec3(-1.0f, 0.0f, 0.0f);

    glm::vec3 current = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 desired = glm::vec3(-2.15f, 3.15f, 0.0f);

    glm::vec3 OX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 OY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 OZ = glm::vec3(0.0f, 0.0f, 1.0f);
};