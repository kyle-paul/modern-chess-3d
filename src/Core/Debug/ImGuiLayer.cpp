#include "Core/Debug/ImGuiLayer.h"
#include "Core/Debug/Logging.h"
#include "Core/Window/Window.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>

ImGuiLayer::ImGuiLayer()
{

}

ImGuiLayer::~ImGuiLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    if (!ImGui_ImplOpenGL3_Init("#version 410")) {
        ERROR("ImGui OpenGL3 Init failed!");
        return;
    }

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 

    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnRender(Environment &env)
{
    Window* window = Window::GetInstance();
    auto &windowSpec = window->m_WindSpec;

    ImGui::Begin("Debug Console");
    ImGui::ColorEdit4("Background color", windowSpec.BgColor);

    ImGui::Text("Camera editor");
    ImGui::DragFloat("Field of view", &env.camera.m_Camspec.FOV, 1.0f, 10.0f, 90.0f);
    ImGui::DragFloat("Near clip", &env.camera.m_Camspec.NearClip, 1.0f, -30.0f, 0.1f);
    ImGui::DragFloat("Far clip", &env.camera.m_Camspec.FarClip, 1.0f, 20.0f, 100.0f);
    ImGui::DragFloat3("Camera position", glm::value_ptr(env.camera.m_Camspec.position), 0.2f, -50.0f, 50.f);
    ImGui::DragFloat3("Camera rotation", glm::value_ptr(env.camera.m_Camspec.rotation), 0.1f, -45.0f, 45.0f);

    ImGui::End();
}