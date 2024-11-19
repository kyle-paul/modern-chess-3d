#pragma once
#include <Core/Render/Shader.h>
#include "Core/Render/VertexArray.h"
#include "Core/Render/Buffer.h"
#include "Core/Render/Model.h"
#include "Core/Game/Square.h"
#include "Core/Game/Config/GameConfig.h"

struct PieceManger
{
    Model Pawn = Model("assets/models/chess/Pawn.obj");
    Model Rook = Model("assets/models/chess/Rook.obj");
    Model Knight = Model("assets/models/chess/Knight.obj");
    Model Bishop = Model("assets/models/chess/Bishop.obj");
    Model King = Model("assets/models/chess/King.obj");
    Model Queen = Model("assets/models/chess/Queen.obj");
};

class Grid
{
public:
    Grid();
    ~Grid();
    
    void Init();
    void Render(const std::shared_ptr<Shader> &gridShader, const GameState &state);

    Square* GetSquare(int row, int col);

private:
    float vertices [4 * 3] = {
        0.0f, 0.0f, 0.5f,
        0.0f, 1.0f, 0.5f,
        1.0f, 1.0f, 0.5f,
        1.0f, 0.0f, 0.5f,
    };
    
    std::shared_ptr<VertexArray> SquareVA;
    std::shared_ptr<VertexBuffer> SquareVB;

    Square m_Squares[10][10];
    PieceManger pieces;

    friend class Board;
};