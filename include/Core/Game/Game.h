#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Game/Config/GameConfig.h"
#include "Core/Render/Shader.h"
#include "Core/Window/WindowConfig.h"
#include "Core/Game/Board.h"
#include "Core/Game/Status.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Run(Environment &env);
    
    static void KeyFunction(int key, int action);

private:
    void BoardRotationTurn(Environment &env, GameState &state);
    void UpdateTurn();

private:
    static GameState state;
    Status status;
    ShaderLibrary shadlib;
    Board m_Board;

    friend class ImGuiLayer;
}; 