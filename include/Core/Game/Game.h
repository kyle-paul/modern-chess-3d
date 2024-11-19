#pragma once
#include "Core/Game/Config/GameConfig.h"
#include "Core/Render/Shader.h"
#include "Core/Window/WindowConfig.h"
#include "Core/Game/Board.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Run(Environment &env);
    void BoardRotationTurn(Environment &env, GameState &state);
    void UpdateTurn();

private:
    GameState state;

    ShaderLibrary shadlib;
    Board m_Board;

    friend class ImGuiLayer;
}; 