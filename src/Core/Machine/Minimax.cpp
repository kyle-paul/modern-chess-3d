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

// Action Minimax::Solve(Board &board, int depth, bool isMax)
// {
//     // Base case (last depth)
//     if (depth == h)
//     {
//         Action action;
//         action.row = 0;
//         action.col = 0;
//         action.score = board.GetEvaluation();
//         return action;
//     }

//     Action chosenAction;

//     // Maximize player
//     if (isMax)
//     {
//         WARN("Max Playing");

//         int maxScore = -1e9;
//         for (auto &record : board.records)
//         {
//             if (record.first->GetColor() == PieceColor::BLACK)
//             {
//                 INFO("Piece: {0} - {1} | position = {2} - {3}", PieceTypeLog(record.first->GetType()), 
//                 PieceColorLog(record.first->GetColor()), record.second.first, record.second.second);

//                 moves = m_Rule.GetValidMoves(p_grid, record.second.first, record.second.second, m_status);
//                 if (moves.size() == 0) continue;

//                 for (auto &move : moves)
//                 {
//                     auto [start_row, start_col] = move.GetOriginPos();
//                     auto [end_row, end_col] = move.GetDestinationPos();
//                     TRACE("Start = {0} - {1} | End = {2} - {3}", start_row, start_col, end_row, end_col);

//                     board.MakeMove(move);
//                     break;
//                 }
//             }
//             std::cout << "\n";
//         }

//         return chosenAction;
        
//         // int maxScore = -1e9;
//         // for (auto &[row, col, piece] : board.records[0])
//         // {
//         //     std::vector<Move> moves = m_Rule.GetValidMoves(row, col, piece);
//         //     for (auto &move : moves)
//         //     {
//         //         board.MakeMove(move);
//         //         Action action = Solve(board, depth+1, false);
//         //         board.RedoMove(move);

//         //         if (action.score > maxScore)
//         //         {
//         //             maxScore = action.score;
//         //             chosenAction = action;
//         //         }
//         //     }
//         // }
//         // return chosenAction;
//     }

//     // Minimize player
//     else
//     {
//         // int minScore = 1e9;
//         // for (auto &[row, col, piece] : board.records[1])
//         // {
//         //     std::vector<Move> moves = m_Rule.GetValidMoves(row, col, piece);
//         //     for (auto &move: moves)
//         //     {
//         //         board.MakeMove(move);
//         //         Action action = Solve(board, depth+1, true);
//         //         board.RedoMove(move);

//         //         if (action.score < minScore)
//         //         {
//         //             minScore = action.score;
//         //             chosenAction = action;
//         //         }
//         //     }
//         // }
//         // return chosenAction;
//     }
// }