#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Core/Render/Framebuffer.h"
#include <memory>

class ImGuiLayer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

public:
    static void Init(GLFWwindow *window);
    void Begin();
    void End();
    void OnRender(std::shared_ptr<Framebuffer> &fb);

private:
    bool rotate = false;
    float m_time = 0.0f;
    float t = 0.0f;
    float speed = 0.01f;

    static glm::vec2 m_ViewportSize;
};