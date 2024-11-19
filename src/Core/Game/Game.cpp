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
    shadlib.Load("square_shader", "assets/shaders/SquareShader.glsl");
    m_Board.Init();
}

void Game::Run(Environment &env)
{
    shadlib.Get("board_shader")->Bind();
    shadlib.Get("board_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    shadlib.Get("board_shader")->SetMat4("model", m_Board.GetTransform());
    m_Board.RenderChessBoard();
    shadlib.Get("board_shader")->UnBind();

    shadlib.Get("square_shader")->Bind();
    shadlib.Get("square_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    m_Board.RenderBoardSquares(shadlib.Get("square_shader"));
    shadlib.Get("square_shader")->UnBind();
}