#include "Core/Machine/Minimax.h"
#include "Core/Debug/Assert.h"
#include <algorithm>
#include <iostream>


Minimax::Minimax(Grid *grid, Status &status, int h) 
    : p_grid(grid), m_status(status), h(h)
{

}

Minimax::~Minimax()
{

}

Action Minimax::Solve(Board &board, int depth, Move &move, bool isMax)
{
    // Base case (last depth)
    if (depth == h)
    {
        Action action;
        action.move = move;
        action.score = board.GetEvaluation();
        return action;
    }

    Action chosenAction;
    chosenAction.move = move;
    chosenAction.score = isMax ? -1e9 : 1e9;

    // Maximize player
    if (isMax)
    {
        WARN("Max Playing");

        int maxScore = -1e9;
        bool flag = false;
        for (auto &record : board.records)
        {
            if (record.first->GetColor() == PieceColor::BLACK)
            {
                moves = m_Rule.GetValidMoves(p_grid, record.second.first, record.second.second, m_status);
                if (moves.size() == 0) continue;

                for (auto &move : moves)
                {
                    board.MakeMove(move);
                    Action action = Solve(board, depth+1, move, false);
                    board.UndoMove();

                    if (action.score > maxScore)
                    {
                        maxScore = action.score;
                        chosenAction = action;
                    }
                }
            }
        }

        return chosenAction;
    }

    // Minimize player
    else
    {
        int minScore = 1e9;
        for (auto &record : board.records)
        {
            if (record.first->GetColor() == PieceColor::WHITE)
            {
                moves = m_Rule.GetValidMoves(p_grid, record.second.first, record.second.second, m_status);
                if (moves.size() == 0) continue;

                for (auto &move : moves)
                {
                    board.MakeMove(move);
                    Action action = Solve(board, depth+1, move, true);
                    board.UndoMove();

                    if (action.score < minScore)
                    {
                        minScore = action.score;
                        chosenAction.score = action.score;
                    }
                }
            }
        }
        return chosenAction;
    }
}

// INFO("Piece: {0} - {1} | position = {2} - {3}", PieceTypeLog(record.first->GetType()), 
// PieceColorLog(record.first->GetColor()), record.second.first, record.second.second);

// auto [start_row, start_col] = move.GetOriginPos();
// auto [end_row, end_col] = move.GetDestinationPos();
// TRACE("Start = {0} - {1} | End = {2} - {3}", start_row, start_col, end_row, end_col);