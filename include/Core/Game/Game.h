#pragma once
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

private:
    ShaderLibrary shadlib;
    Board m_Board;
}; 