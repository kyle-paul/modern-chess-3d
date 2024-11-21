#include "Core/Debug/ImGuiLayer.h"
#include "Core/Debug/Logging.h"
#include "Core/Window/Window.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>

glm::vec2 ImGuiLayer::m_ViewportSize;

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

static const char* turns[]{"Black", "White"};
static const char* modes[]{"Two players", "Classic machine", "Deep learning"};
static int mode;

void ImGuiLayer::OnRender(std::shared_ptr<Framebuffer> &fb)
{
    Window *window = Window::GetInstance();

    fb->Bind();
    auto [mx, my] = ImGui::GetMousePos();
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        if (mx > 0 && mx < m_ViewportSize.x && my > 0 && my < m_ViewportSize.y)
        {
            int row = fb->ReadPixel(1, (int)mx, (int)my);
            int col = fb->ReadPixel(2, (int)mx, (int)my);

            if (1 <= row  && row <= 8 && 1 <= col && col <= 8)
            {
                if (!window->m_Game.state.Selected)
                {
                    window->m_Game.state.SelectedRow = row;
                    window->m_Game.state.SelectedCol = col;
                }
                else 
                {
                    window->m_Game.state.DesRow = row;
                    window->m_Game.state.DesCol = col;
                }
                window->m_Game.ControllMove();
            }
        }
    }    
    fb->Unbind();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    
    auto &windowSpec = window->m_WindSpec;
    auto &env = window->m_Env;

    ImGui::Begin("Debug Console");
    ImGui::ColorEdit4("Background color", windowSpec.BgColor);

    ImGui::Text("Camera editor");
    ImGui::DragFloat("Field of view", &env.camera.m_Camspec.FOV, 1.0f, 10.0f, 90.0f);
    ImGui::DragFloat("Near clip", &env.camera.m_Camspec.NearClip, 1.0f, -30.0f, 0.1f);
    ImGui::DragFloat("Far clip", &env.camera.m_Camspec.FarClip, 1.0f, 20.0f, 100.0f);
    ImGui::DragFloat3("Camera position", glm::value_ptr(env.camera.m_Camspec.position), 0.2f, -50.0f, 50.f);
    ImGui::DragFloat3("Camera rotation", glm::value_ptr(env.camera.m_Camspec.rotation), 0.1f, -45.0f, 45.0f);

    ImGui::Text("Game controller");
    ImGui::Combo("Color turn", &window->m_Game.state.Turn, turns, IM_ARRAYSIZE(turns));
    ImGui::Checkbox("Board rotating", &window->m_Game.state.BoardRotating);

    ImGui::Text("Environment controller");
    ImGui::DragFloat3("Light direction", glm::value_ptr(env.lighting.light_direction), 0.2f, -50.0f, 50.0f);

    ImGui::Text("Chess board");
    ImGui::DragFloat3("Board position", glm::value_ptr(window->m_Game.m_Board.position), 0.1f, -20.0f, 20.f);
    ImGui::DragFloat3("Board rotation", glm::value_ptr(window->m_Game.m_Board.rotation), 0.1f, -45.0f, 45.0f);

    ImGui::Text("Game options");
    ImGui::Combo("Playing mode", &mode , modes, IM_ARRAYSIZE(modes));
    ImGui::End();


    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Viewport");

    ImVec2 viewportpanelsize = ImGui::GetContentRegionAvail();
    
    if (m_ViewportSize != *(glm::vec2*)&viewportpanelsize)
    {
        m_ViewportSize = { viewportpanelsize.x, viewportpanelsize.y };
        window->fb->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
    }

	unsigned int textureID = window->fb->GetColorAttachmentID();
	ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });

	ImGui::End();
    ImGui::PopStyleVar();
}