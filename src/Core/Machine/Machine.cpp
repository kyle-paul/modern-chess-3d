#include "Core/Machine/Machine.h"
#include "Core/Debug/Assert.h"
#include <algorithm>
#include <iostream>
#include <random>

Machine::Machine(Grid *grid, Status &status, int h, int h2) 
    : p_grid(grid), m_status(status), h(h), h2(h2)
{

}

Machine::~Machine()
{

}

Action Machine::AlphaBeta(Board &board, int alpha, int beta, int depth, Move &move, bool isMax)
{
    // Base case: reached maximum depth
    if (depth == h2)
    {
        Action action;
        action.move = move;
        action.score = board.GetEvaluation();
        return action;
    }

    Action chosenAction;
    chosenAction.move = move;
    chosenAction.score = isMax ? -1e9 : 1e9;

    std::vector<Action> bestActions;

    if (isMax) // Maximizing player
    {
        int maxScore = -1e9;

        for (auto &record : board.records)
        {
            if (record.first->GetColor() == PieceColor::BLACK)
            {
                moves = m_Rule.GetValidMoves(p_grid, record.second.first, record.second.second, m_status);
                if (moves.empty()) continue;

                for (auto &move : moves)
                {
                    board.MakeMove(move);
                    Action action = AlphaBeta(board, alpha, beta, depth + 1, move, false);
                    board.UndoMove();

                    if (action.score > maxScore)
                    {
                        maxScore = action.score;
                        chosenAction = action;

                        bestActions.clear();
                        bestActions.push_back(action);
                    }
                    else if (action.score == maxScore)
                    {
                        bestActions.push_back(action);
                    }

                    alpha = std::max(alpha, maxScore);
                    if (beta <= alpha) break; // Prune
                }
            }
        }
    }
    else // Minimizing player
    {
        int minScore = 1e9;

        for (auto &record : board.records)
        {
            if (record.first->GetColor() == PieceColor::WHITE)
            {
                moves = m_Rule.GetValidMoves(p_grid, record.second.first, record.second.second, m_status);
                if (moves.empty()) continue;

                for (auto &move : moves)
                {
                    board.MakeMove(move);
                    Action action = AlphaBeta(board, alpha, beta, depth + 1, move, true);
                    board.UndoMove();

                    if (action.score < minScore)
                    {
                        minScore = action.score;
                        chosenAction = action;

                        bestActions.clear();
                        bestActions.push_back(action);
                    }
                    else if (action.score == minScore)
                    {
                        bestActions.push_back(action);
                    }

                    beta = std::min(beta, minScore);
                    if (beta <= alpha) break; // Prune
                }
            }
        }
    }

    // Randomly select from equally best moves
    if (!bestActions.empty())
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, bestActions.size() - 1);
        chosenAction = bestActions[dis(gen)];
    }

    return chosenAction;
}

Action Machine::Minimax(Board &board, int depth, Move &move, bool isMax)
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

    std::vector<Action> bestActions;

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
                    Action action = Minimax(board, depth+1, move, false);
                    board.UndoMove();

                    if (action.score > maxScore)
                    {
                        maxScore = action.score;
                        chosenAction = action;
                    }

                    else if (action.score == maxScore)
                    {
                        bestActions.push_back(action);
                    }
                }
            }
        }

        if (!bestActions.empty())
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, bestActions.size() - 1);
            chosenAction = bestActions[dis(gen)];
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
                    Action action = Minimax(board, depth+1, move, true);
                    board.UndoMove();

                    if (action.score < minScore)
                    {
                        minScore = action.score;
                        chosenAction.score = action.score;
                    }

                    else if (action.score == minScore)
                    {
                        bestActions.push_back(action);
                    }
                }
            }
        }
        
        if (!bestActions.empty())
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, bestActions.size() - 1);
            chosenAction = bestActions[dis(gen)];
        }

        return chosenAction;
    }
}

Action Machine::RandomMove(Board &board)
{
    std::vector<Move> allMoves;

    for (auto &record : board.records)
    {
        if (record.first->GetColor() == PieceColor::BLACK)
        {
            moves = m_Rule.GetValidMoves(p_grid, record.second.first, record.second.second, m_status);
            allMoves.insert(allMoves.end(), moves.begin(), moves.end());
        }
    }

    if (allMoves.empty())
    {
        return Action();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allMoves.size() - 1);
    Move selectedMove = allMoves[dis(gen)];

    Action randomAction;
    randomAction.move = selectedMove;
    
    return randomAction;
}

// INFO("Piece: {0} - {1} | position = {2} - {3}", PieceTypeLog(record.first->GetType()), 
// PieceColorLog(record.first->GetColor()), record.second.first, record.second.second);

// auto [start_row, start_col] = move.GetOriginPos();
// auto [end_row, end_col] = move.GetDestinationPos();
// TRACE("Start = {0} - {1} | End = {2} - {3}", start_row, start_col, end_row, end_col);