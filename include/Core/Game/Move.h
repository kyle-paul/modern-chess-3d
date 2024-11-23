#pragma once
#include "Core/Game/Piece.h"
#include "Core/Game/Config/MoveConfig.h"
#include <utility>
#include <memory>

struct MoveState 
{
    Piece* moved;
    Piece* captured;
    std::pair<int, int> start;
    std::pair<int, int> end;
    MoveType type;
};

class Move
{
public:
    Move(const Move& move);
    Move(const MoveController &controller);
    Move(MoveType type, int fRow, int fCol, int tRow, int tCol, Piece* moved, Piece* captured=nullptr);
    ~Move();

    std::pair<int, int> GetOriginPos();
    std::pair<int, int> GetDestinationPos();

    Piece* GetMovedPiece() { return m_Controller.MovedPiece; } 
    Piece*  GetCapturedPiece() { return m_Controller.CapturedPiece; }
    MoveType GetType() { return m_Controller.type; }

private:
    MoveController m_Controller;
};