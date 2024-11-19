#include "Core/Game/Rule.h"

Rule::Rule()
{

}

Rule::~Rule()
{
}

void Rule::GetValidMovePawn(const GameState &state, std::vector<Move> &moves, Piece *piece)
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
    if (state.SrcRow + up1 <= MAX_ROW_INDEX)
    {
        moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, state.SrcRow + up1, state.SrcCol, piece, nullptr));
        if (p_Grid->GetSquare(state.SrcRow + up1, state.SrcCol)->GetOccupiedState())
            moves.pop_back();
    }

    if (moves.size() && state.SrcRow == secondrow)
    {
        moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, state.SrcRow + up2, state.SrcCol, piece, nullptr));
        if (p_Grid->GetSquare(state.SrcRow + 2, state.SrcCol)->GetOccupiedState())
            moves.pop_back();                    
    }

    // Normal capture
    if(state.SrcRow >= MIN_ROW_INDEX && state.SrcRow <= MAX_ROW_INDEX && state.SrcCol >= MIN_COL_INDEX && state.SrcCol <= MAX_COL_INDEX)
    {
        if(p_Grid->GetSquare(state.SrcRow, state.SrcCol)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(state.SrcRow, state.SrcCol)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, state.SrcRow + up1, state.SrcCol + left, piece, p_Grid->GetSquare(state.SrcRow, state.SrcCol)->GetPiece()));
            }
        }
    }

    if(state.SrcRow >= MIN_ROW_INDEX && state.SrcRow <= MAX_ROW_INDEX && state.SrcCol >= MIN_COL_INDEX && state.SrcCol <= MAX_COL_INDEX)
    {
        if(p_Grid->GetSquare(state.SrcRow, state.SrcCol)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(state.SrcRow, state.SrcCol)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, state.SrcRow + up1, state.SrcCol + right, piece, p_Grid->GetSquare(state.SrcRow, state.SrcCol)->GetPiece()));
            }
        }
    }
    
    // en passant
    if (state.SrcRow == middle)
    {
        if(state.SrcCol >= MIN_COL_INDEX && p_Grid->GetSquare(state.SrcRow + up1, state.SrcCol + left)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(state.SrcRow, state.SrcCol + left)->GetOccupiedState())
            {
                Piece* capPossibility = p_Grid->GetSquare(state.SrcRow, state.SrcCol - 1)->GetPiece();

                if(capPossibility->GetType() == PieceType::PAWN && capPossibility->GetColor() != piece->GetColor())
                {
                    moves.push_back(Move(MoveType::EN_PASSANT, state.SrcRow, state.SelectedCol, state.SrcRow + up1, state.SrcCol + left, piece, capPossibility));
                }
            }
        }

        if(state.SrcCol <= MAX_COL_INDEX && p_Grid->GetSquare(state.SrcRow + up1, state.SrcCol + right)->GetOccupiedState())
        {
            if(p_Grid->GetSquare(state.SrcRow, state.SrcCol + right)->GetOccupiedState())
            {
                Piece* capPossibility = p_Grid->GetSquare(state.SrcRow, state.SrcCol + 1)->GetPiece();

                if(capPossibility->GetType() == PieceType::PAWN && capPossibility->GetColor() != piece->GetColor())
                {
                    moves.push_back(Move(MoveType::EN_PASSANT, state.SrcRow, state.SelectedCol, state.SrcRow + up1, state.SrcCol + right, piece, capPossibility));
                }
            }
        }
    }
}

void Rule::GetValidMoveRook(const GameState &state, std::vector<Move> &moves, Piece *piece)
{
    // Move upward
    int row = state.SrcRow, col = state.SrcCol;
    while (row < MAX_ROW_INDEX)
    {
        row++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move downward
    row = state.SrcRow, col = state.SrcCol;
    while (row > MIN_ROW_INDEX)
    {
        row--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move left
    row = state.SrcRow, col = state.SrcCol;
    while (col > MIN_COL_INDEX)
    {
        col--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move right
    row = state.SrcRow, col = state.SrcCol;
    while (col < MAX_COL_INDEX)
    {
        col++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if(p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }
}

void Rule::GetValidMoveBishop(const GameState &state, std::vector<Move> &moves, Piece *piece)
{
    // Move left upward
    int row = state.SrcRow, col = state.SrcCol;
    while(row < MAX_ROW_INDEX && col > MIN_COL_INDEX)
    {
        row++; col--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move right upward
    row = state.SrcRow, col = state.SrcCol;
    while(row < MAX_ROW_INDEX && col < MAX_ROW_INDEX)
    {
        row++; col++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move left downward
    row = state.SrcRow, col = state.SrcCol;
    while(row > MIN_ROW_INDEX && col > MIN_COL_INDEX)
    {
        row--; col--;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }

    // Move right downward
    row = state.SrcRow, col = state.SrcCol;
    while(row > MIN_ROW_INDEX && col < MAX_COL_INDEX)
    {
        row--; col++;
        if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
        {
            moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
        }
        else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
        {
            moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            break;
        }
        else break;
    }
}

void Rule::GetValidMoveKnight(const GameState &state, std::vector<Move> &moves, Piece *piece)
{
    int control_x[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int control_y[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

    for (int k=0; k<8; k++)
    {
        int row = state.SrcRow + control_x[k];
        int col = state.SrcCol + control_y[k];

        if (MIN_ROW_INDEX <= row && row <= MAX_ROW_INDEX  && MIN_COL_INDEX <= col && col <= MAX_COL_INDEX)
        {
            if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
            {
                moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
            }
            else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            }
        }
    }
}

void Rule::GetValidMoveQueen(const GameState &state, std::vector<Move> &moves, Piece *piece)
{
    // merge two moves from rook and bishop
    std::vector<Move> moveRook, moveBishop;
    GetValidMoveRook(state, moveRook, piece);
    GetValidMoveBishop(state, moveBishop, piece);

    for (auto move : moveRook)
    {
        moves.push_back(move);
    }

    for (auto move : moveBishop)
    {
        moves.push_back(move);
    }
}

void Rule::GetValidMoveKing(const GameState &state, std::vector<Move> &moves, Piece *piece, Status &status)
{
    // Normal move
    int control_x[8] = {1, 1, 0, -1, -1, -1,  0, 1};
    int control_y[8] = {0, 1, 1,  1,  0, -1, -1, -1};

    for (int k=0; k<8; k++)
    {
        int row = state.SrcRow + control_x[k];
        int col = state.SrcCol + control_y[k];

        if (MIN_ROW_INDEX <= row && row <= MAX_ROW_INDEX && MIN_COL_INDEX <= col && col <= MAX_COL_INDEX)
        {
            if (!p_Grid->GetSquare(row, col)->GetOccupiedState())
            {
                moves.push_back(Move(MoveType::NORMAL, state.SrcRow, state.SrcCol, row, col, piece, nullptr));
            }
            else if (p_Grid->GetSquare(row, col)->GetPiece()->GetColor() != piece->GetColor())
            {
                moves.push_back(Move(MoveType::CAPTURE, state.SrcRow, state.SrcCol, row, col, piece, p_Grid->GetSquare(row, col)->GetPiece()));
            }
        }
    }

    // Castling
    if(!status.IsKingMove(piece->GetColor()) && !status.IsFirstColRookMove(piece->GetColor()))
    {
        if(!p_Grid->GetSquare(state.SrcRow, state.SrcCol - 1)->GetOccupiedState() && !p_Grid->GetSquare(state.SrcRow, state.SrcCol - 2)->GetOccupiedState())
            moves.push_back(Move(MoveType::CASTLING, state.SrcRow, state.SrcCol, state.SrcRow, state.SrcCol - 2, piece));
    }
    if(!status.IsKingMove(piece->GetColor()) && !status.IsLastColRookMove(piece->GetColor()))
    {
        if(p_Grid->GetSquare(state.SrcRow, state.SrcCol + 1)->GetOccupiedState() && !p_Grid->GetSquare(state.SrcRow, state.SrcCol + 2)->GetOccupiedState())
            moves.push_back(Move(MoveType::CASTLING, state.SrcRow, state.SrcCol, state.SrcRow, state.SrcCol + 2, piece));
    }
}

std::vector<Move> Rule::GetValidMoves(Grid &grid, const GameState &state, Status &status)
{
    p_Grid = &grid;
    std::vector<Move> moves;
    
    Piece *piece = p_Grid->GetSquare(state.SrcRow, state.SrcCol)->GetPiece();
    if (!piece) 
        return moves;

    switch(piece->GetType())
    {
        case PieceType::PAWN: GetValidMovePawn(state, moves, piece); break;
        case PieceType::ROOK: GetValidMoveRook(state, moves, piece); break;
        case PieceType::BISHOP: GetValidMoveBishop(state, moves, piece); break;
        case PieceType::KNIGHT: GetValidMoveKnight(state, moves, piece); break;
        case PieceType::QUEEN: GetValidMoveQueen(state, moves, piece); break;
        case PieceType::KING: GetValidMoveKing(state, moves, piece, status); break;
    }

    return std::move(moves);
}