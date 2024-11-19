#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Window/WindowConfig.h"

class ImGuiLayer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

public:
    static void Init(GLFWwindow *window);
    void Begin();
    void End();
    void OnRender(Environment &env);

private:
    
};