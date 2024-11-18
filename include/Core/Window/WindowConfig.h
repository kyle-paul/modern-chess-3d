#pragma once
#include <string>
#include <glm/glm.hpp>

struct WindowSpec
{
    int Width, Height;
    float Aspect;
    glm::vec4 BgColor;
    std::string Title;

    WindowSpec(const std::string& title = "3D Chess Game",
			   int width = 1200, int height = 900, 
               float aspect = 1200.0f / 900.0f,
               glm::vec4 color = glm::vec4(0.2f, 0.2f, 0.2f, 0.8f))
        : Title(title), Width(width), Height(height), Aspect(aspect), BgColor(color)
    { 
        
    }
};