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
    shadlib.Load("grid_shader", "assets/shaders/SquareShader.glsl");
    shadlib.Load("piece_shader", "assets/shaders/PieceShader.glsl");
    m_Board.Init();
}

void Game::BoardRotationTurn(Environment &env, GameState &state)
{
    switch(state.TurnColor)
    {
        case PieceColor::WHITE:
        {
            if (env.camera.m_Camspec.time <= 1.0f && state.Turn % 2 == 1) 
            {
                env.camera.m_Camspec.rotation = env.camera.InterpolateWhite();
                env.camera.m_Camspec.time += 0.01f;
            }
            else state.BoardRotating = false;
            break;
        }
        case PieceColor::BLACK:
        {
            if (env.camera.m_Camspec.time > 1.0f && env.camera.m_Camspec.time <= 2.0f && state.Turn % 2 == 0) 
            {
                env.camera.m_Camspec.rotation = env.camera.InterpolateBlack();
                env.camera.m_Camspec.time += 0.01f;
            }
            else 
            {
                env.camera.m_Camspec.time = 0.0f;
                state.BoardRotating = false;
            }
            break;
        }
    }
}

void Game::Run(Environment &env)
{
    if (state.BoardRotating) 
        BoardRotationTurn(env, state);

    shadlib.Get("board_shader")->Bind();
    shadlib.Get("board_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    shadlib.Get("board_shader")->SetMat4("model", m_Board.GetTransform());
    m_Board.RenderChessBoard();
    shadlib.Get("board_shader")->UnBind();

    shadlib.Get("grid_shader")->Bind();
    shadlib.Get("grid_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    m_Board.RenderGrid(shadlib.Get("grid_shader"), state);
    shadlib.Get("grid_shader")->UnBind();

    shadlib.Get("piece_shader")->Bind();
    shadlib.Get("piece_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    m_Board.RenderPieces(shadlib.Get("piece_shader"), state, env);
    shadlib.Get("piece_shader")->UnBind();

    UpdateTurn();
}


void Game::UpdateTurn()
{
    state.TurnColor = (state.Turn & 1) ? PieceColor::WHITE : PieceColor::BLACK;
}