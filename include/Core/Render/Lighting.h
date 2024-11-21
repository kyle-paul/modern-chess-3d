#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

class Lighting
{
public:
    Lighting() {}; 
    ~Lighting() {};

    const glm::vec3 InterpolateWhite(float &t) const { return glm::lerp(current_light, desired_light, t); } 
    const glm::vec3 InterpolateBlack(float &t) const { return glm::lerp(desired_light, current_light, t); } 

public:
    glm::vec3 current_light = glm::vec3(15.0f, -50.0f, -50.0f);
    glm::vec3 desired_light = glm::vec3(0.0f, -4.6f, -2.6f);
    glm::vec3 light_direction = current_light;

private:
};