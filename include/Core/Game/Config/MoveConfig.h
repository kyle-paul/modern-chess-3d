#pragma once
#include <memory>

enum class MoveType
{
    NORMAL     = 0,
	CAPTURE    = 1,
	EN_PASSANT = 2,
	CASTLING   = 3,
};

struct MoveController
{
    int srcRow; int srcCol;    
    int desRow; int desCol;

    MoveType type;
    Piece* MovedPiece;
    Piece* CapturedPiece;
};