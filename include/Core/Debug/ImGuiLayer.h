#pragma once
#include <glad/glad.h>
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
    bool rotate = false;
    float m_time = 0.0f;
    float t = 0.0f;
    float speed = 0.01f;
};