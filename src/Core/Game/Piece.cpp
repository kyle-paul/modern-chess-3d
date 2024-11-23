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

const std::string PieceTypeLog(const PieceType &type)
{
	switch(type)
	{
		case PieceType::PAWN: return "PAWN"; break;
		case PieceType::ROOK: return "ROOK"; break;
		case PieceType::KNIGHT: return "KNIGHT"; break;
		case PieceType::BISHOP: return "BISHOP"; break;
		case PieceType::KING: return "KING"; break;
		case PieceType::QUEEN: return "QUEEN"; break;
	}
	ASSERT(false, "Invalid PieceType");
	return "None";
}

const std::string PieceColorLog(const PieceColor &color)
{
	switch(color)
	{
		case PieceColor::BLACK: return "BLACK"; break;
		case PieceColor::WHITE: return "WHITE"; break;
	}
	ASSERT(false, "Invalid PieceColor");
	return "None";
}