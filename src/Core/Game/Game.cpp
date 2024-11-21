#include "Core/Game/Game.h"
#include "Core/Debug/Logging.h"

GameState Game::state;
Status Game::status;

Game::Game()
{

}

Game::~Game()
{
    
}

void Game::Init()
{
    shadlib.Load("board_shader", "assets/shaders/BoardShader.glsl");
    shadlib.Load("grid_shader", "assets/shaders/GridShader.glsl");
    shadlib.Load("piece_shader", "assets/shaders/PieceShader.glsl");
    m_Board.Init();
}

void Game::BoardRotationTurn(Environment &env, GameState &state)
{
    state.TurnColor = (state.Turn & 1) ? PieceColor::WHITE : PieceColor::BLACK;
    switch(state.TurnColor)
    {
        case PieceColor::WHITE:
        {
            if (env.camera.m_Camspec.time <= 1.0f && state.Turn % 2 == 1) 
            {
                env.camera.m_Camspec.rotation = env.camera.InterpolateWhite();
                env.lighting.light_direction = env.lighting.InterpolateWhite(env.camera.m_Camspec.time);
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
                env.lighting.light_direction = env.lighting.InterpolateBlack(env.camera.m_Camspec.time);
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
    m_Board.RenderValidMove(shadlib.Get("grid_shader"), state, status);
    m_Board.RenderMoveToSquare(shadlib.Get("grid_shader"), state);
    shadlib.Get("grid_shader")->UnBind();

    shadlib.Get("piece_shader")->Bind();
    shadlib.Get("piece_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    m_Board.RenderPieces(shadlib.Get("piece_shader"), state, env);
    shadlib.Get("piece_shader")->UnBind();
}

void Game::UpdateTurn()
{
    state.Selected = false;
    state.NeedPromote = false;
    state.Check = false;

    state.BoardRotating = true;
    state.Turn++;
    state.TurnColor = (state.Turn & 1) ? PieceColor::WHITE : PieceColor::BLACK;

    switch(state.TurnColor)
    {
        case PieceColor::WHITE:
            state.SelectedRow = 1;
            state.SelectedCol = 8;
            break;
        case PieceColor::BLACK:
            state.SelectedRow = 8;
            state.SelectedCol = 1;
            break;
    }
}


void Game::KeyFunction(int &key, int &action)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        int direction = 0;
        switch(state.TurnColor)
        {
            case PieceColor::WHITE: direction = 1; break;
            case PieceColor::BLACK: direction = -1; break;
        }

        if (state.SelectedCol <= 8 && state.SelectedCol >= 1 && !state.Selected)
        {
            state.SelectedCol += direction;
        }
        else if (state.DesCol <= 8 && state.DesCol >= 1 && state.Selected)
        {
            state.DesCol += direction;
        }
    }

    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        int direction = 0;
        switch(state.TurnColor)
        {
            case PieceColor::WHITE: direction = 1; break;
            case PieceColor::BLACK: direction = -1; break;
        }

        if (state.SelectedRow <= 8 && state.SelectedRow >= 1 && !state.Selected)
        {
            state.SelectedRow += direction;
        }
        else if (state.DesRow <= 8 && state.DesRow >= 1 && state.Selected)
        {
            state.DesRow += direction;
        }
    }

    else if(key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        int direction = 0;
        switch(state.TurnColor)
        {
            case PieceColor::WHITE: direction = 1; break;
            case PieceColor::BLACK: direction = -1; break;
        }

        if (state.SelectedRow >= 1 && state.SelectedRow <= 8 && !state.Selected)
        {
            state.SelectedRow -= direction;
        }
        else if(state.DesRow >= 1 && state.DesRow <= 8 && state.Selected)
        {
            state.DesRow -= direction;
        }
    }

    else if(key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        int direction = 0;
        switch(state.TurnColor)
        {
            case PieceColor::WHITE: direction = 1; break;
            case PieceColor::BLACK: direction = -1; break;
        }

        if (state.SelectedCol >= 1 && state.SelectedCol <= 8 && !state.Selected)
        {
            state.SelectedCol -= direction;
        }
        else if(state.DesCol > 1 && state.DesCol <= 8 && state.Selected)
        {
            state.DesCol -= direction;
        }
    }

    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        ControllMove();
    }
}

void Game::ControllMove()
{
    if (!state.Selected)
    {
        if (m_Board.m_Grid.GetSquare(state.SelectedRow, state.SelectedCol)->GetOccupiedState())
        {
            state.Selected = true;
            state.SrcRow = state.SelectedRow;
            state.SrcCol = state.SelectedCol;
            state.DesRow = state.SelectedRow;
            state.DesCol = state.SelectedCol;
        }
    }

    else 
    {
        if ((state.DesRow == state.SrcRow) && (state.DesCol == state.SrcCol))
        {
            state.Selected = false;
        }
        else if (m_Board.MovePlayer(state, status))
        {
            Piece *piece = m_Board.m_Grid.GetSquare(state.DesRow, state.DesCol)->GetPiece();
            if (piece->GetType() == PieceType::PAWN &&
                ((piece->GetColor() == PieceColor::BLACK && state.DesRow == m_Board.MIN_ROW_INDEX) ||
                (piece->GetColor() == PieceColor::WHITE && state.DesRow == m_Board.MAX_COL_INDEX))
                )
            {
                state.NeedPromote = true;
            }
            UpdateTurn();
        }
    }
}