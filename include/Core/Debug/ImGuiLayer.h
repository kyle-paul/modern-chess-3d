#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <memory>
#include "Core/Render/Framebuffer.h"
#include "Core/Render/Texture.h"

class ImGuiLayer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

public:
    void Init(GLFWwindow *window);
    void Begin();
    void End();
    void OnRender(std::shared_ptr<Framebuffer> &fb);

private:
    bool rotate = false;
    float m_time = 0.0f;
    float t = 0.0f;
    float speed = 0.01f;

    static glm::vec2 m_ViewportSize;
    static ImFont* boldFont;
    static ImFont* menuFont;

    std::shared_ptr<Texture2D> bg;
    float window_width = 400.0f;
    float window_height = 200.0f;
    float button_width = 120.0f;
    float button_padding = 10.0f;

    float panel_width = 450.0f;
    float panel_height = 600.0f;
};