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

class Machine
{
public:
    Machine() = default;
    Machine(Grid *grid, Status &status, int h, int h2);
    ~Machine();

    Action Minimax(Board &board, int depth, Move &move, bool isMax);
    Action AlphaBeta(Board &board, int alpha, int beta, int depth, Move &move, bool isMax);
    Action RandomMove(Board &board);

private:
    int h, h2;
    Rule m_Rule;
    Grid *p_grid;
    Status m_status;
    std::vector<Move> moves;
};