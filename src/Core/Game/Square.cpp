#include "Core/Game/Square.h"
#include "Core/Debug/Assert.h"

Square::Square()
{
	m_OccupyingPiece = nullptr;
}

Square::Square(const Square& square)
{
	this->m_OccupyingPiece = square.m_OccupyingPiece;
}

Piece* Square::RemovePiece()
{
    Piece* RemovedPiece = m_OccupyingPiece;
    m_OccupyingPiece = nullptr;
    return RemovedPiece;
}

Piece* Square::GetPiece()
{
    return m_OccupyingPiece;
}

bool Square::SetOccupied(Piece* piece)
{
    if (GetOccupiedState())
        return false;
    else
    {
        m_OccupyingPiece = piece;
        return true;
    }
}

bool Square::GetOccupiedState()
{
    return m_OccupyingPiece != nullptr;
}