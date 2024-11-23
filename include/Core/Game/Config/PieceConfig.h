#pragma once
#include <string>
#include "Core/Debug/Assert.h"

enum class PieceType : int
{
	PAWN 	= 0,
	ROOK 	= 1,
	KNIGHT 	= 2,
	BISHOP	= 3,
	KING	= 4,
	QUEEN	= 5
};

enum class PieceColor : int
{
	BLACK,
	WHITE
};

struct PieceProps
{
	PieceType Type;
	PieceColor Color;
};

const std::string PieceTypeLog(const PieceType &type);
const std::string PieceColorLog(const PieceColor &color);