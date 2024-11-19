#pragma once

#include "Core/Game/Piece.h"
#include "Core/Game/Config/PieceConfig.h"

class Status
{
public:
    Status();
    Status(const Status &status);
    ~Status();

public:
    void SetKingMove(PieceColor color);
    void SetPieceEnPassantable(PieceColor color, Piece *piece);
    void SetFirstColRookMove(PieceColor color);
    void SetLastColRookMove(PieceColor color);  

    bool IsKingMove(PieceColor color);
    bool IsFirstColRookMove(PieceColor color);
    bool IsLastColRookMove(PieceColor color);
    Piece* PieceEnPassantable(PieceColor color);

private:
    bool whiteKingMove;
    bool blackKingMove;
    
    Piece* whitePieceEnPassant;
    Piece* blackPieceEnPassant;
    
    bool whiteFirstColRookMove;
    bool whiteLastColRookMove;
    bool blackFirstColRookMove;
    bool blackLastColRookMove;
};