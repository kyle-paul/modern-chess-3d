#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Window/Window.h"
#include "Core/Debug/Logging.h"
#include "Core/Debug/Assert.h"
#include "Core/Render/Renderer.h"
#include "Core/Debug/ImGuiLayer.h"

Window *Window::m_WinInstance = nullptr;

Window::Window()
{
    ASSERT(!m_WinInstance, "Window already exits!");
    m_WinInstance = this;
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::KeyFunction(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Window::Init()
{
    if (!glfwInit())
    {
        ERROR("Could not initialize GLFW window!");
        exit(-1);
    }

    m_Window = glfwCreateWindow(m_WindSpec.Width, m_WindSpec.Height, 
                                m_WindSpec.Title.c_str(), NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        ERROR("Creating GLFW window failed!");
        exit(-1);
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetKeyCallback(m_Window, KeyFunction);
    Renderer::Init();
    m_Game.Init();
    ImGuiLayer::Init(m_Window);
}

void Window::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        // Framebuffer resize
        int display_w, display_h;
        glfwGetFramebufferSize(m_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        m_WindSpec.Aspect = (float)display_w / (float)display_h;
        m_Env.camera.m_Camspec.Aspect = m_WindSpec.Aspect;

        // Clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(m_WindSpec.BgColor[0], m_WindSpec.BgColor[1], 
                     m_WindSpec.BgColor[2], m_WindSpec.BgColor[3]);

        // Run the Game
        m_Game.Run(m_Env);

        // Imgui Render
        m_Gui.Begin();
        m_Gui.OnRender();
        m_Gui.End();
        
        // Swap buffer
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
