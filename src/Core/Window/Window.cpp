#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Window/Window.h"
#include "Core/Debug/Logging.h"
#include "Core/Debug/Assert.h"
#include "Core/Render/Renderer.h"
#include "Core/Debug/ImGuiLayer.h"
#include "imgui.h"

Window *Window::m_WinInstance = nullptr;
WindowSpec Window::m_WindSpec;

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

    Game* gameInstance = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (gameInstance) 
    {
        gameInstance->KeyFunction(key, action);
    }
}

void Window::MouseFunction(GLFWwindow* window, int button, int action, int mods)
{
    // if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
    // {
    //     auto [mx, my] = ImGui::GetMousePos();
    //     if (mx > 0 && mx < m_WindSpec.Width && my > 0 && my < m_WindSpec.Height)
    //     {
    //         int pixel = fbo_instance->ReadPixel(1, (int)mx, (int)my);
    //         INFO("Mouse = {0} - {1}", mx, my);
    //     }
    // }
    // fbo_instance->Unbind();
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
    glfwSetWindowUserPointer(m_Window, &m_Game);
    glfwSetWindowUserPointer(m_Window, &fb);
    glfwSetKeyCallback(m_Window, KeyFunction);
    glfwSetMouseButtonCallback(m_Window, MouseFunction);

    Renderer::Init();
    m_Game.Init();
    ImGuiLayer::Init(m_Window);

    FramebufferConfig fbspec;
    fbspec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
    fbspec.Width = 1200.0f;
	fbspec.Height = 810.0f;
	fb = Framebuffer::Create(fbspec);
}

void Window::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        // Framebuffer resizeFramebufferTextureFormat::RED_INTEGER
        int display_w, display_h;
        glfwGetFramebufferSize(m_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        m_WindSpec.Aspect = (float)display_w / (float)display_h;
        m_Env.camera.m_Camspec.Aspect = m_WindSpec.Aspect;

        // Clear color
        fb->Bind();
        fb->ClearAttachment(1, -1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(m_WindSpec.BgColor[0], m_WindSpec.BgColor[1], 
                     m_WindSpec.BgColor[2], m_WindSpec.BgColor[3]);

        // // Run the Game
        m_Game.Run(m_Env);
        fb->Unbind();

        // Imgui Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_Gui.Begin();
        m_Gui.OnRender(fb);
        m_Gui.End();

        // Swap buffer
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}