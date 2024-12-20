#include "Core/Debug/ImGuiLayer.h"
#include "Core/Debug/Logging.h"
#include "Core/Window/Window.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>


glm::vec2 ImGuiLayer::m_ViewportSize;
ImFont* ImGuiLayer::boldFont;
ImFont* ImGuiLayer::menuFont;

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
    bg = Texture2D::Create("assets/ui/imgs/bg.png");

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

    io.Fonts->AddFontFromFileTTF("assets/ui/fonts/Arial.ttf", 14.0f);
    boldFont = io.Fonts->AddFontFromFileTTF("assets/ui/fonts/Berkshire.ttf", 40.0f);
    menuFont = io.Fonts->AddFontFromFileTTF("assets/ui/fonts/Arial.ttf", 20.0f);

    ImVec4 *colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.5f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 15;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 7;
    style.ChildRounding = 4;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 4;
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
static const char* modes[]{"Human", "Easy", "Minimax", "AlphaBeta", "DeepLearning"};
static int mode = 0;

void ImGuiLayer::OnRender(std::shared_ptr<Framebuffer> &fb)
{
    Window *window = Window::GetInstance();
    auto &windowSpec = window->m_WindSpec;
    auto &env = window->m_Env;

    window->m_Game.state.mode = (Mode)mode;

    fb->Bind();
    if (window->m_Running)
    {
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
    }
    fb->Unbind();

    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    if (window->m_Running)
    {        
        ImGui::Begin("Setting Console");

        // Environment controller
        if (ImGui::TreeNode("Environment Controller")) {
            ImGui::ColorEdit4("Background color", windowSpec.BgColor);
            ImGui::DragFloat3("Light direction", glm::value_ptr(env.lighting.light_direction), 0.2f, -50.0f, 50.0f);
            ImGui::TreePop();
        }

        // Chess board
        if (ImGui::TreeNode("Chess Board")) {
            // Change color of board
            ImGui::DragFloat3("Board position", glm::value_ptr(window->m_Game.board.position), 0.1f, -20.0f, 20.f);
            ImGui::DragFloat3("Board rotation", glm::value_ptr(window->m_Game.board.rotation), 0.1f, -45.0f, 45.0f);
            ImGui::ColorEdit4("Board color", glm::value_ptr(window->m_Game.board.boardColor));
            ImGui::ColorEdit4("First player color", glm::value_ptr(window->m_Game.board.firstPlayerColor));
            ImGui::ColorEdit4("Second player color", glm::value_ptr(window->m_Game.board.secPlayerColor));
            ImGui::TreePop();
        }

        // Camera editor
        if (ImGui::TreeNode("Camera Editor")) {
            ImGui::DragFloat("Field of view", &env.camera.m_Camspec.FOV, 1.0f, 10.0f, 90.0f);
            ImGui::DragFloat("Near clip", &env.camera.m_Camspec.NearClip, 1.0f, -30.0f, 0.1f);
            ImGui::DragFloat("Far clip", &env.camera.m_Camspec.FarClip, 1.0f, 20.0f, 100.0f);
            ImGui::DragFloat3("Camera position", glm::value_ptr(env.camera.m_Camspec.position), 0.2f, -50.0f, 50.f);
            ImGui::DragFloat3("Camera rotation", glm::value_ptr(env.camera.m_Camspec.rotation), 0.1f, -45.0f, 45.0f);
            ImGui::TreePop();
        }

        // Game controller
        if (ImGui::TreeNode("Game Options")) {
            ImGui::Combo("Playing mode", &mode, modes, IM_ARRAYSIZE(modes));
            ImGui::Combo("Color turn", &window->m_Game.state.Turn, turns, IM_ARRAYSIZE(turns));
            ImGui::Checkbox("Board rotating", &window->m_Game.state.BoardRotating);
            ImGui::TreePop();
        } 

        ImGui::End();
    }
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Viewport");

    ImVec2 viewportpanelsize = ImGui::GetContentRegionAvail();
    
    if (m_ViewportSize != *(glm::vec2*)&viewportpanelsize)
    {
        m_ViewportSize = { viewportpanelsize.x, viewportpanelsize.y };
        window->fb->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
    }

    if (window->m_Running)
    {
        unsigned int textureID = window->fb->GetColorAttachmentID();
        ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });
    }
    else
    {
        unsigned int textureID = bg->GetRendererID();
        ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y });
    }
	
	ImGui::End();
    ImGui::PopStyleVar();

    if (!window->m_Running)
    {
        ImVec2 window_pos = ImVec2((m_ViewportSize.x - window_width) / 2.0f, 
                              (m_ViewportSize.y - window_height) / 2.0f);
        ImVec2 window_size = ImVec2(window_width, window_height);

        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("game_menu", nullptr,
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoTitleBar);

        ImGui::PushFont(boldFont);
        float text_width = ImGui::CalcTextSize("Modern 3D Chess Game").x;
        ImGui::SetCursorPosX((window_width - text_width) / 2.0f);
        ImGui::Text("Modern 3D Chess Game");
        ImGui::PopFont();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
    
        ImGui::PushFont(menuFont);
        ImGui::SetCursorPosX((window_width - button_width) / 2.0f);
        if (ImGui::Button("Start Game", ImVec2(button_width, 0)))
            window->m_Running = true;
        ImGui::Dummy(ImVec2(0.0f, button_padding));

        ImGui::SetCursorPosX((window_width - button_width) / 2.0f);
        if (ImGui::Button("Load Game", ImVec2(button_width, 0))) 
        {
            // Open Dialog
            window->m_Game.seri.load(&window->m_Game.state, &window->m_Game.board, &window->m_Game.status);
            window->m_Running = true;
        }

        ImGui::SetCursorPosX((window_width - button_width) / 2.0f);
        if (ImGui::Button("Settings", ImVec2(button_width, 0))) 
        {
            
        }
        ImGui::Dummy(ImVec2(0.0f, button_padding));

        ImGui::SetCursorPosX((window_width - button_width) / 2.0f);
        if (ImGui::Button("Exit", ImVec2(button_width, 0))) {
            glfwSetWindowShouldClose(window->m_Window, true);
        }
        ImGui::PopFont();
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
}