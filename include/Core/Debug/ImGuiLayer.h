#pragma once
#include <GLFW/glfw3.h>

class ImGuiLayer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

public:
    static void Init(GLFWwindow *window);
    void Begin();
    void End();
    void OnRender();

private:
    
};