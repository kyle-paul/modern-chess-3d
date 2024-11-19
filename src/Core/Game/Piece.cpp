#include "Core/Game/Piece.h"

Piece::Piece(const Piece &piece)
{
    this->m_PieceProp = piece.m_PieceProp;
}

Piece::Piece(PieceType type, PieceColor color)
{
    m_PieceProp.Type = type;
    m_PieceProp.Color = color;
}

Piece::Piece(PieceProps prop)
    :m_PieceProp(prop)
{
}