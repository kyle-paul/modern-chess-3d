#pragma once
#include "Core/Game/Move.h"
#include "Core/Game/Status.h"
#include "Core/Game/Config/GameConfig.h"
#include "Core/Game/Config/MoveConfig.h"
#include "Core/Game/Grid.h"
#include <vector>

class Rule
{
public:
    Rule();
    ~Rule();

    std::vector<Move> GetValidMoves(Grid &grid, const GameState &state, Status &status);

private:
    Grid *p_Grid;

    const int MIN_COL_INDEX = 1;
    const int MIN_ROW_INDEX = 1;
    const int MAX_COL_INDEX = 8;
    const int MAX_ROW_INDEX = 8;

    void GetValidMovePawn(const GameState &state, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveRook(const GameState &state, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveBishop(const GameState &state, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveKnight(const GameState &state, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveQueen(const GameState &state, std::vector<Move> &moves, Piece *piece);
    void GetValidMoveKing(const GameState &state, std::vector<Move> &moves, Piece *piece, Status &status);
};