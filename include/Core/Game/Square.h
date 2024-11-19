#pragma once
#include "Core/Game/Piece.h"

class Square
{
public:
    Square();
    Square(const Square& square);
    bool SetOccupied(Piece* piece);
    bool GetOccupiedState();

    Piece* RemovePiece();
    Piece* GetPiece();

private:
    bool m_OccupiedState = false;
    Piece* m_OccupyingPiece;
};