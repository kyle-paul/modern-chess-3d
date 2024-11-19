#include "Core/Game/Game.h"
#include "Core/Debug/Logging.h"

Game::Game()
{
    state.Selected = false;
    state.SelectedRow = 1; 
    state.SelectedCol = 1;
    
    state.SrcRow = 0;
    state.SrcCol = 0;
    state.DesRow = 0; 
    state.DesCol = 0;
    
    state.CloseGame = false;
    state.BoardRotating = true;
    state.Check = false;
    state.CheckMate = false;
    state.NeedPromote = false;
    state.Verify = false;
    
    state.Turn = 1;
    state.TurnColor = PieceColor::WHITE;
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

    shadlib.Get("square_shader")->Bind();
    shadlib.Get("square_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    m_Board.RenderBoardSquares(shadlib.Get("square_shader"), state);
    shadlib.Get("square_shader")->UnBind();

    UpdateTurn();
}


void Game::UpdateTurn()
{
    state.TurnColor = (state.Turn & 1) ? PieceColor::WHITE : PieceColor::BLACK;
}