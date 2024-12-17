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

const PieceType PieceTypeLoad(const std::string &type)
{
	if (type == "PAWN") return PieceType::PAWN;
	else if (type == "ROOK") return PieceType::ROOK;
	else if (type == "KNIGHT") return PieceType::KNIGHT;
	else if (type == "BISHOP") return PieceType::BISHOP;
	else if (type == "KING") return PieceType::KING;
	else if (type == "QUEEN") return PieceType::QUEEN;
	else {
		ERROR("Undefined piece type");
		return PieceType::PAWN;
	}
}

const PieceColor PieceColorLoad(const std::string &color)
{
	if (color == "BLACK") return PieceColor::BLACK;
	else if (color == "WHITE") return PieceColor::WHITE;
	else {
		ERROR("Undefined piece color");
		return PieceColor::BLACK;
	}
}