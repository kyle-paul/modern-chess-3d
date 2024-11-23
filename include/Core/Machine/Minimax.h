#pragma once
#include <vector>
#include "Core/Game/Board.h"
#include "Core/Game/Rule.h"
#include "Core/Game/Grid.h"
#include "Core/Game/Status.h"

struct Action
{
    int row, col;
    int score;
};

class Minimax
{
public:
    Minimax() = default;
    Minimax(Grid *grid, Status &status, int h);
    ~Minimax();

    // Action Solve(Board &board, int depth, bool isMax);

private:
    int h;
    Rule m_Rule;
    Grid *p_grid;
    Status m_status;
    std::vector<Move> moves;
};