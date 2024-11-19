#include "Core/Game/Game.h"
#include "Core/Debug/Logging.h"

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::Init()
{
    shadlib.Load("board_shader", "assets/shaders/BoardShader.glsl");
    INFO("Shader {0} loaded successfully", shadlib.Get("board_shader")->GetName());

    m_Board.Init();
}

void Game::Run(Environment &env)
{
    shadlib.Get("board_shader")->Bind();
    shadlib.Get("board_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    m_Board.RenderChessBoard();
    shadlib.Get("board_shader")->UnBind();
}