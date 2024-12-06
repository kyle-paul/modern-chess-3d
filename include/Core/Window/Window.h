#pragma once
#include "Core/Window/WindowConfig.h"
#include "Core/Debug/ImGuiLayer.h"
#include "Core/Game/Game.h"
#include "glui.h"

class Window
{
public:
    Window();
    ~Window();

    void Init();
    void Run();
    
    inline static Window* GetInstance() { return m_WinInstance; } 

private:
    static void KeyFunction(GLFWwindow* window, int key, int scancode, int action, int mods);

    inline glm::ivec2 getRelMousePosition() 
    {
        double x = 0, y = 0;
		glfwGetCursorPos(m_Window, &x, &y);
		return { x, y };
    }

private:
    static Window* m_WinInstance;
    static WindowSpec m_WindSpec;

    GLFWwindow* m_Window;
    ImGuiLayer m_Gui;
    Game m_Game;
    Environment m_Env;

    bool m_Running = false;

    std::shared_ptr<Framebuffer> fb;
    friend class ImGuiLayer;
};