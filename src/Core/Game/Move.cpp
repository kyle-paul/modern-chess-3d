#include "Core/Game/Move.h"
#include <iostream>

Move::Move(const Move& move)
{
    m_Controller = move.m_Controller;
}

Move::Move(const MoveController &controller)
{
    this->m_Controller = controller;
}

Move::Move(MoveType type, int src_row, int src_col, int des_row, int des_col, Piece* moved, Piece* captured)
{
    m_Controller.type = type;
    m_Controller.srcRow = src_row;
    m_Controller.srcCol = src_col;
    m_Controller.desRow = des_row;
    m_Controller.desCol = des_col;
    m_Controller.MovedPiece = moved;
    m_Controller.CapturedPiece = captured;

}

Move::~Move()
{
    
}

std::pair<int, int> Move::GetOriginPos()
{
	return {m_Controller.srcRow, m_Controller.srcCol};
}

std::pair<int, int> Move::GetDestinationPos()
{
    return {m_Controller.desRow, m_Controller.desCol};
}