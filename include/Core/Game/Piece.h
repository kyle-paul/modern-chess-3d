#pragma once
#include "Core/Game/Config/PieceConfig.h"

class Piece
{
public:
    Piece(const Piece &piece);
    Piece(PieceType type, PieceColor color);
    Piece(PieceProps prop);

public:
    PieceType GetType() { return m_PieceProp.Type; }
    PieceColor GetColor() { return m_PieceProp.Color; } 

private:
    PieceProps m_PieceProp;
};