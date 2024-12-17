#pragma once
#include "Core/Game/Move.h"
#include "Core/Game/Status.h"
#include "Core/Game/Config/GameConfig.h"
#include "Core/Game/Config/MoveConfig.h"
#include "Core/Game/Grid.h"
#include <vector>

class Board;

class Rule
{
public:
    Rule();
    ~Rule();

    std::vector<Move> GetValidMoves(Grid *grid, int srcrow, int srccol, Status &status);
    bool isCheckState(Status &status, Board* board, PieceColor color);
    bool isCheckMateState(Status* status, Board* board, PieceColor color);
    bool pawnPromotion(Board* board, int row, int col, PieceType promoteTo);

private:
    Grid *p_Grid;

    const int MIN_COL_INDEX = 1;
    const int MIN_ROW_INDEX = 1;
    const int MAX_COL_INDEX = 8;
    const int MAX_ROW_INDEX = 8;

    void GetValidMovePawn(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveRook(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveBishop(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveKnight(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveQueen(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveKing(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece, Status &status);
};