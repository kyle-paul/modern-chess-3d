#pragma once
#include "Core/Window/WindowConfig.h"
#include "Core/Debug/ImGuiLayer.h"
#include "Core/Game/Game.h"

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
    static void MouseFunction(GLFWwindow* window, int button, int action, int mods);

private:
    static Window* m_WinInstance;
    static WindowSpec m_WindSpec;
    GLFWwindow* m_Window;
    ImGuiLayer m_Gui;
    Game m_Game;
    Environment m_Env;

    std::shared_ptr<Framebuffer> fb;
    friend class ImGuiLayer;
};