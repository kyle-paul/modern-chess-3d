#include "Core/Window/Window.h"
#include "Core/Debug/Logging.h"
#include "Core/Debug/Assert.h"
#include "Core/Render/Renderer.h"

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

        // Clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(m_WindSpec.BgColor.x, m_WindSpec.BgColor.y, 
                     m_WindSpec.BgColor.z, m_WindSpec.BgColor.w);
        
        // Swap buffer
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
