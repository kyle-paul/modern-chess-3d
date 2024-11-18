#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Window/WindowConfig.h"

class Window
{
public:
    Window();
    ~Window();

    void Init();
    void Run();

private:
    static void KeyFunction(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    static Window* m_WinInstance;
    GLFWwindow* m_Window;
    WindowSpec m_WindSpec;
};