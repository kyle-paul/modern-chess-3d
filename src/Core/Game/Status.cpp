#include "Core/Game/Status.h"

Status::Status()
{
    whiteKingMove = false;
	blackKingMove = false;
	whitePieceEnPassant = nullptr;
	blackPieceEnPassant = nullptr;
	whiteFirstColRookMove = false;
	whiteLastColRookMove = false;
	blackFirstColRookMove = false;
	blackLastColRookMove = false;
}

Status::Status(const Status &status)
{
    this->whiteKingMove = status.whiteKingMove;
	this->blackKingMove = status.blackKingMove;
	this->whitePieceEnPassant = status.whitePieceEnPassant;
	this->blackPieceEnPassant = status.blackPieceEnPassant;
	this->whiteFirstColRookMove = status.whiteFirstColRookMove;
	this->whiteLastColRookMove = status.whiteLastColRookMove;
	this->blackFirstColRookMove = status.blackFirstColRookMove;
	this->blackLastColRookMove = status.blackLastColRookMove;
}

Status::~Status()
{

}

void Status::SetKingMove(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE: whiteKingMove = true; break;
        case PieceColor::BLACK: blackKingMove = true; break;
    }
}

void Status::SetPieceEnPassantable(PieceColor color, Piece *piece)
{
    switch(color)
    {
        case PieceColor::WHITE: whitePieceEnPassant = piece; break;
        case PieceColor::BLACK: blackPieceEnPassant = piece; break;
    }
}

void Status::SetFirstColRookMove(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE: whiteFirstColRookMove = true; break;
        case PieceColor::BLACK: blackFirstColRookMove = true; break;
    }
}

void Status::SetLastColRookMove(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE: whiteLastColRookMove = true; break;
        case PieceColor::BLACK: blackLastColRookMove = true; break;
    }
}  

bool Status::IsKingMove(PieceColor color)
{
    if(color==PieceColor::WHITE) return whiteKingMove;
	else return blackKingMove;
}

bool Status::IsFirstColRookMove(PieceColor color)
{
    if(color==PieceColor::WHITE) return whiteFirstColRookMove;
	else return blackFirstColRookMove;
}

bool Status::IsLastColRookMove(PieceColor color)
{
	if(color==PieceColor::WHITE) return whiteLastColRookMove;
	else return blackLastColRookMove;
}

Piece* Status::PieceEnPassantable(PieceColor color)
{
    if(color==PieceColor::WHITE) return whitePieceEnPassant;
	else return blackPieceEnPassant;
}