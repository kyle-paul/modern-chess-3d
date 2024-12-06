#pragma once
#include "Core/Render/Camera.h"
#include "Core/Render/Lighting.h"
#include <string>
#include <glm/glm.hpp>

struct WindowSpec
{
    int Width, Height;
    float Aspect;
    float BgColor[4] = {0.2f, 0.2f, 0.2f, 0.8f};
    std::string Title;

    WindowSpec(const std::string& title = "3D Chess Game",
			   int width = 1200, int height = 810, 
               float aspect = 1500.0f / 900.0f)
        : Title(title), Width(width), Height(height), Aspect(aspect)
    { 
        
    }
};

struct Environment
{
    Camera camera;
    Lighting lighting;
};