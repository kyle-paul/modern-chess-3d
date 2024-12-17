#include "Core/Game/Rule.h"
#include "Core/Game/Board.h"

Rule::Rule()
{

}

Rule::~Rule()
{
}

void Rule::GetValidMovePawn(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece)
{
    int up1, up2, left, right, secondrow, middle;
    switch (piece->GetColor())
    {
        case PieceColor::WHITE:
        {
            up1 = 1; up2 = 2; left = -1; right = 1; secondrow = MIN_ROW_INDEX + 1;
            middle = MIN_ROW_INDEX + 4;
            break;
        }
        case PieceColor::BLACK:
        {
            up1 = -1, up2 = -2; left = 1; right = -1, secondrow = MAX_ROW_INDEX - 1;
            middle = MAX_ROW_INDEX - 4;
            break;
        }
    }

    // Normal move
    if (srcrow + up1 <= MAX_ROW_INDEX)
    {
        if (!p_Grid->GetSquare(srcrow + up1, srccol)->GetOccupiedState())
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, srcrow + up1, srccol, piece, nullptr));
    }

    if (moves.size() && srcrow == secondrow)
    {
        if (!p_Grid->GetSquare(srcrow + up2, srccol)->GetOccupiedState())
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, srcrow + up2, srccol, piece, nullptr));                   
    }

    // Normal capture
    if(srcrow >= MIN_ROW_INDEX && srcrow <= MAX_ROW_INDEX && srccol >= MIN_COL_INDEX && srccol <= MAX_COL_INDEX)
    {
        if(p_Grid->GetSquare(srcrow + up1, srccol + left)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(srcrow + up1, srccol + left)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, srcrow + up1, srccol + left, piece, p_Grid->GetSquare(srcrow + up1, srccol + left)->GetPiece()));
            }
        }
    }

    if(srcrow >= MIN_ROW_INDEX && srcrow <= MAX_ROW_INDEX && srccol >= MIN_COL_INDEX && srccol <= MAX_COL_INDEX)
    {
        if(p_Grid->GetSquare(srcrow + up1, srccol + right)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(srcrow + up1, srccol + right)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, srcrow + up1, srccol + right, piece, p_Grid->GetSquare(srcrow + up1, srccol + right)->GetPiece()));
            }
        }
    }
    
    // en passant
    if (srcrow == middle)
    {
        if(srccol >= MIN_COL_INDEX && p_Grid->GetSquare(srcrow + up1, srccol + left)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(srcrow, srccol + left)->GetOccupiedState())
            {
                Piece* capPossibility = p_Grid->GetSquare(srcrow, srccol - 1)->GetPiece();

                if(capPossibility->GetType() == PieceType::PAWN && capPossibility->GetColor() != piece->GetColor())
                {
                    moves.push_back(Move(MoveType::EN_PASSANT, srcrow, srccol, srcrow + up1, srccol + left, piece, capPossibility));
                }
            }
        }

        if(srccol <= MAX_COL_INDEX && p_Grid->GetSquare(srcrow + up1, srccol + right)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(srcrow, srccol + right)->GetOccupiedState())
            {
                Piece* capPossibility = p_Grid->GetSquare(srcrow, srccol + 1)->GetPiece();

                if(capPossibility->GetType() == PieceType::PAWN && capPossibility->GetColor() != piece->GetColor())
                {
                    moves.push_back(Move(MoveType::EN_PASSANT, srcrow, srccol, srcrow + up1, srccol + right, piece, capPossibility));
                }
            }
        }
    }
}

void Rule::GetValidMoveRook(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece)
{
    // Move upward
    int row = srcrow, col = srccol;
    while (row < MAX_ROW_INDEX)
    {
        row++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move downward
    row = srcrow, col = srccol;
    while (row > MIN_ROW_INDEX)
    {
        row--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move left
    row = srcrow, col = srccol;
    while (col > MIN_COL_INDEX)
    {
        col--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move right
    row = srcrow, col = srccol;
    while (col < MAX_COL_INDEX)
    {
        col++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }
}

void Rule::GetValidMoveBishop(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece)
{
    // Move left upward
    int row = srcrow, col = srccol;
    while(row < MAX_ROW_INDEX && col > MIN_COL_INDEX)
    {
        row++; col--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move right upward
    row = srcrow, col = srccol;
    while(row < MAX_ROW_INDEX && col < MAX_ROW_INDEX)
    {
        row++; col++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move left downward
    row = srcrow, col = srccol;
    while(row > MIN_ROW_INDEX && col > MIN_COL_INDEX)
    {
        row--; col--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move right downward
    row = srcrow, col = srccol;
    while(row > MIN_ROW_INDEX && col < MAX_COL_INDEX)
    {
        row--; col++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }
}

void Rule::GetValidMoveKnight(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece)
{
    int control_x[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int control_y[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

    for (int k=0; k<8; k++)
    {
        int row = srcrow + control_x[k];
        int col = srccol + control_y[k];

        if (MIN_ROW_INDEX <= row && row <= MAX_ROW_INDEX  && MIN_COL_INDEX <= col && col <= MAX_COL_INDEX)
        {
            if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
            {
                moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
            }
            else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            }
        }
    }
}

void Rule::GetValidMoveQueen(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece)
{
    // merge two moves from rook and bishop
    std::vector<Move> moveRook, moveBishop;
    GetValidMoveRook(srcrow, srccol, moveRook, piece);
    GetValidMoveBishop(srcrow, srccol, moveBishop, piece);

    for (auto move : moveRook)
    {
        moves.push_back(move);
    }

    for (auto move : moveBishop)
    {
        moves.push_back(move);
    }
}

void Rule::GetValidMoveKing(int srcrow, int srccol, std::vector<Move> &moves, Piece *piece, Status &status)
{
    // Normal move
    int control_x[8] = {1, 1, 0, -1, -1, -1,  0, 1};
    int control_y[8] = {0, 1, 1,  1,  0, -1, -1, -1};

    for (int k=0; k<8; k++)
    {
        int row = srcrow + control_x[k];
        int col = srccol + control_y[k];

        if (MIN_ROW_INDEX <= row && row <= MAX_ROW_INDEX && MIN_COL_INDEX <= col && col <= MAX_COL_INDEX)
        {
            if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
            {
                moves.push_back(Move(MoveType::NORMAL, srcrow, srccol, row, col, piece, nullptr));
            }
            else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, srcrow, srccol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            }
        }
    }

    // Castling
    if(!status.IsKingMove(piece->GetColor()) && !status.IsFirstColRookMove(piece->GetColor()))
    {
        if(!p_Grid->GetSquare(srcrow, srccol - 1)->GetOccupiedState() && !p_Grid->GetSquare(srcrow, srccol - 2)->GetOccupiedState())
            moves.push_back(Move(MoveType::CASTLING, srcrow, srccol, srcrow, srccol - 2, piece));
    }
    if(!status.IsKingMove(piece->GetColor()) && !status.IsLastColRookMove(piece->GetColor()))
    {
        if(p_Grid->GetSquare(srcrow, srccol + 1)->GetOccupiedState() && !p_Grid->GetSquare(srcrow, srccol + 2)->GetOccupiedState())
            moves.push_back(Move(MoveType::CASTLING, srcrow, srccol, srcrow, srccol + 2, piece));
    }
}

std::vector<Move> Rule::GetValidMoves(Grid *grid, int srcrow, int srccol, Status &status)
{
    p_Grid = grid;
    std::vector<Move> moves;
    
    Piece *piece = p_Grid->GetSquare(srcrow, srccol)->GetPiece();
    if (!piece) 
        return moves;

    switch(piece->GetType())
    {
        case PieceType::PAWN: GetValidMovePawn(srcrow, srccol, moves, piece); break;
        case PieceType::ROOK: GetValidMoveRook(srcrow, srccol, moves, piece); break;
        case PieceType::BISHOP: GetValidMoveBishop(srcrow, srccol, moves, piece); break;
        case PieceType::KNIGHT: GetValidMoveKnight(srcrow, srccol, moves, piece); break;
        case PieceType::QUEEN: GetValidMoveQueen(srcrow, srccol, moves, piece); break;
        case PieceType::KING: GetValidMoveKing(srcrow, srccol, moves, piece, status); break;
    }

    return std::move(moves);
}

bool Rule::isCheckState(Status &status, Board* board, PieceColor color)
{
    int kingRow, kingCol;
    std::vector<Move> moves;
    Piece *actPiece;

    for (auto &record : board->records)
    {
        if (record.first->GetType() == PieceType::KING && record.first->GetColor() == color)
        {
            kingRow, kingCol = record.second.first, record.second.second;
            break;
        }
    }

    for (auto &record : board->records)
    {
        if (record.first->GetColor() != color)
        {
            moves = GetValidMoves(&board->m_Grid, record.second.first, record.second.second, status);
            for (auto &move : moves)
            {
                if (move.GetDestinationPos().first == kingRow && move.GetDestinationPos().second == kingCol)
                {
                    return true;
                }
            }
            moves.clear();
        }
    }
    return false;
}

bool Rule::isCheckMateState(Status* status, Board* board, PieceColor color)
{
    return false;   
}

bool Rule::pawnPromotion(Board* board, int row, int col, PieceType promoteTo)
{
    return false;
}