#pragma once
#include <vector>
#include "Core/Game/Board.h"
#include "Core/Game/Rule.h"
#include "Core/Game/Grid.h"
#include "Core/Game/Status.h"

struct Action
{
    Move move;
    int score;

    Action() : move(Move(MoveType::NORMAL, 0,0,0,0, nullptr, nullptr)), score(0) {}
};

class Minimax
{
public:
    Minimax() = default;
    Minimax(Grid *grid, Status &status, int h);
    ~Minimax();

    Action Solve(Board &board, int depth, Move &move, bool isMax);

private:
    int h;
    Rule m_Rule;
    Grid *p_grid;
    Status m_status;
    std::vector<Move> moves;
};