#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Game/Config/GameConfig.h"
#include "Core/Render/Shader.h"
#include "Core/Window/WindowConfig.h"
#include "Core/Game/Board.h"
#include "Core/Game/Status.h"
#include "Core/Render/Framebuffer.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Run(Environment &env);
    
    void KeyFunction(int &key, int &action);

private:
    void BoardRotationTurn(Environment &env, GameState &state);
    void UpdateTurn();
    void ControllMove();

private:
    static GameState state;
    static Status status;
    Board m_Board;
    ShaderLibrary shadlib;

    friend class ImGuiLayer;
    friend class Window;
}; 