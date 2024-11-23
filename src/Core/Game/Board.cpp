#include "Core/Game/Board.h"
#include "Core/Render/Renderer.h"

Board::Board()
{

}

Board::Board(const Board& board)
{

}

Board::~Board()
{

}

void Board::Init()
{
    boardVA = VertexArray::Create();
    boardVB = VertexBuffer::Create(vertices, sizeof(vertices));
    boardVB->SetLayout({
        { ShaderDataType::Float3, "a_Position", false },
        { ShaderDataType::Float3, "a_Color",  false },
    });
    boardVA->AddVertexBuffer(boardVB);
    m_Grid.Init();
    SetInitialPieces(PieceColor::WHITE);
    SetInitialPieces(PieceColor::BLACK);
}

const glm::mat4 Board::GetTransform() const
{
    return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation));
}

void Board::SetInitialPieces(const PieceColor &color)
{
    int firstrow, secondrow, index;
    switch(color)
    {
        case PieceColor::WHITE:
        {
            firstrow = MIN_ROW_INDEX;
            secondrow = MIN_ROW_INDEX + 1;
            index = 0;
            break;
        }
        case PieceColor::BLACK:
        {
            firstrow = MAX_ROW_INDEX;
            secondrow = MAX_ROW_INDEX - 1;
            index = 1;
            break;
        }
    }   

    int firstcol = MIN_COL_INDEX;

    for (int col=firstcol; col <= MAX_COL_INDEX; col++)
    {
        m_Grid.GetSquare(secondrow, col)->SetOccupied(new Piece(PieceType::PAWN, color));
        records[m_Grid.GetSquare(secondrow, col)->GetPiece()] = {secondrow, col};
    }

    // ROOK
	m_Grid.GetSquare(firstrow, firstcol)->SetOccupied(new Piece(PieceType::ROOK, color));
	m_Grid.GetSquare(firstrow, firstcol + 7)->SetOccupied(new Piece(PieceType::ROOK, color));

    records[m_Grid.GetSquare(firstrow, firstcol)->GetPiece()] = {firstrow, firstcol};
    records[m_Grid.GetSquare(firstrow, firstcol + 7)->GetPiece()] = {firstrow, firstcol + 7};

	// KNIGHT
	m_Grid.GetSquare(firstrow, firstcol + 1)->SetOccupied(new Piece(PieceType::KNIGHT, color));
	m_Grid.GetSquare(firstrow, firstcol + 6)->SetOccupied(new Piece(PieceType::KNIGHT, color));

    records[m_Grid.GetSquare(firstrow, firstcol + 1)->GetPiece()] = {firstrow, firstcol + 1};
    records[m_Grid.GetSquare(firstrow, firstcol + 6)->GetPiece()] = {firstrow, firstcol + 6};

	// BISHOP
	m_Grid.GetSquare(firstrow, firstcol + 2)->SetOccupied(new Piece(PieceType::BISHOP, color));
	m_Grid.GetSquare(firstrow, firstcol + 5)->SetOccupied(new Piece(PieceType::BISHOP, color));

    records[m_Grid.GetSquare(firstrow, firstcol + 2)->GetPiece()] = {firstrow, firstcol + 2};
    records[m_Grid.GetSquare(firstrow, firstcol + 5)->GetPiece()] = {firstrow, firstcol + 5};
    
	// QUEEN
	m_Grid.GetSquare(firstrow, firstcol + 3)->SetOccupied(new Piece(PieceType::QUEEN, color));
    records[m_Grid.GetSquare(firstrow, firstcol + 3)->GetPiece()] = {firstrow, firstcol + 3};

	// KING
	m_Grid.GetSquare(firstrow, firstcol + 4)->SetOccupied(new Piece(PieceType::KING, color));
    records[m_Grid.GetSquare(firstrow, firstcol + 4)->GetPiece()] = {firstrow, firstcol + 4};
}

void Board::RenderChessBoard()
{
    Renderer::Draw(boardVA, true, 36);
}

void Board::RenderGrid(const std::shared_ptr<Shader> &gridShader, const GameState &state)
{
    m_Grid.Render(gridShader, state);
}

void Board::RenderPieces(const std::shared_ptr<Shader> &pieceShader,  const GameState &state, const Environment &env)
{
    // if (state.thinking) return; // computer is thinking
    float z = 0.0f;
    float r, c;
    glm::vec3 rotation;
    
    for (int row=1; row <= 8; row++)
    {
        for (int col=1; col <= 8; col++)
        {
            if (m_Grid.GetSquare(row, col)->GetOccupiedState())
            {
                if (state.Selected && row == state.SrcRow && col == state.SrcCol)
                {
                    z = 1.0f;
                }
                else z = 0.55f;

                r = (row - 5) * 1.0f + 0.5f;
                c = (col - 5) * 1.0f + 0.5f;

                switch(m_Grid.GetSquare(row, col)->GetPiece()->GetColor())
                {
                    case PieceColor::WHITE:
                    {
                        rotation = glm::vec3(0, 0, glm::radians(180.0f));
                        pieceShader->SetFloat3("v_color", glm::vec3(0.9f, 0.9f, 0.9f));
                        break;
                    }
                    case PieceColor::BLACK:
                    {
                        rotation = glm::vec3(0, 0, glm::radians(360.0f));
                        pieceShader->SetFloat3("v_color", glm::vec3(0.2f, 0.2f, 0.2f));
                        break;
                    }
                }

                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(c, r, z)) *
                                  glm::toMat4(glm::quat(rotation)) *
                                  glm::scale(glm::mat4(1.0f), glm::vec3(0.014f, 0.014f, 0.014f));
                pieceShader->SetMat4("model", model);
                pieceShader->SetFloat3("light_direction", env.lighting.light_direction);
                pieceShader->SetInt("v_row", row);
                pieceShader->SetInt("v_col", col);

                switch(m_Grid.GetSquare(row, col)->GetPiece()->GetType())
                {
                    case PieceType::PAWN: m_Grid.pieces.Pawn.Render(); break;
                    case PieceType::ROOK: m_Grid.pieces.Rook.Render(); break;
                    case PieceType::KNIGHT: m_Grid.pieces.Knight.Render(); break;
                    case PieceType::BISHOP: m_Grid.pieces.Bishop.Render(); break;
                    case PieceType::KING: m_Grid.pieces.King.Render(); break;
                    case PieceType::QUEEN: m_Grid.pieces.Queen.Render(); break;
                }
            }
        }
    }
}

void Board::RenderMoveToSquare(const std::shared_ptr<Shader> &gridShader, const GameState &state)
{
    float r = 1.0 * (state.DesRow - 5);
    float c = 1.0 * (state.DesCol - 5);

    if (state.Selected)
    {
        m_Grid.m_Quad.Render(gridShader, glm::vec3(c, r, 0.011f), 7);
    }
}

void Board::RenderValidMove(const std::shared_ptr<Shader> &gridShader, const GameState &state, Status &status)
{
    if (!state.Selected)
        return;

    int r,c;       
    moves = m_Rule.GetValidMoves(&m_Grid, state.SrcRow, state.SrcCol, status);

    for (auto &move : moves)
    {
        auto DestPos = move.GetDestinationPos();
        int type;

        gridShader->SetInt("v_row", DestPos.first);
        gridShader->SetInt("v_col", DestPos.second);

        switch(move.GetType())
        {
            case MoveType::NORMAL: type = 3; break;
            case MoveType::CAPTURE: type = 4; break;
            case MoveType::EN_PASSANT: type = 5; break;
            case MoveType::CASTLING: type = 6; break;
        }

        r = 1.0 * (DestPos.first - 5);
        c = 1.0 * (DestPos.second - 5);
        m_Grid.m_Quad.Render(gridShader, glm::vec3(c, r, 0.01f), type);
    }
}

bool Board::MovePlayer(const GameState &state, Status &status)
{   
    for (auto &move : moves)
    {
        auto end = move.GetDestinationPos();

        if (end.first == state.DesRow && end.second == state.DesCol)
        {
            Piece* piece = move.GetMovedPiece();
            auto start = move.GetOriginPos();

            {
                MoveState moveState;
                moveState.moved = piece;
                moveState.start = start;
                moveState.end = end;
                moveState.type = move.GetType();
                moveState.captured = move.GetCapturedPiece();
                moveHistory.push(moveState);
            }

            switch(move.GetType())
            {
                case MoveType::NORMAL:
                {
                    if (piece->GetType() == PieceType::PAWN && (start.first - end.first) == 2)
                    {
                        status.SetPieceEnPassantable(piece->GetColor(), piece);
                    }
                    else if (piece->GetType() == PieceType::KING)
                    {
                        status.SetKingMove(piece->GetColor());
                    }
                    else if (piece->GetType() == PieceType::ROOK)
                    {
                        if (start.second == MIN_COL_INDEX) status.SetFirstColRookMove(piece->GetColor());
                        else if (start.second == MAX_COL_INDEX) status.SetLastColRookMove(piece->GetColor());
                    }
                    records[piece] = {end.first, end.second};
                    return m_Grid.GetSquare(end.first, end.second)->SetOccupied(m_Grid.GetSquare(start.first, start.second)->RemovePiece());
                }
                
                case MoveType::CAPTURE:
                {
                    if (piece->GetType() == PieceType::KING)
                    {
                        status.SetKingMove(piece->GetColor());
                    }
                    else if (piece->GetType() == PieceType::ROOK)
                    {
                        if (start.second == MIN_COL_INDEX) status.SetFirstColRookMove(piece->GetColor());
                        else if (start.second == MAX_COL_INDEX) status.SetLastColRookMove(piece->GetColor());
                    }

                    records[piece] = {end.first, end.second};
                    records.erase(move.GetCapturedPiece());
                    
                    m_Grid.GetSquare(end.first, end.second)->RemovePiece();
                    return m_Grid.GetSquare(end.first, end.second)->SetOccupied(m_Grid.GetSquare(start.first, start.second)->RemovePiece());
                }
                
                case MoveType::CASTLING:
                {
                    int RookOriginCol = ((end.second < start.second) ? MIN_COL_INDEX : MAX_COL_INDEX);
                    int RookDestCol = ((end.second < start.second) ? start.second - 1 : start.second + 1);

                    records[piece] = {end.first, end.second};
                    records[m_Grid.GetSquare(start.first, RookOriginCol)->GetPiece()] = {end.first, RookDestCol};

                    m_Grid.GetSquare(end.first, end.second)->SetOccupied(m_Grid.GetSquare(start.first, start.second)->RemovePiece());
                    m_Grid.GetSquare(end.first, RookDestCol)->SetOccupied(m_Grid.GetSquare(start.first, RookOriginCol)->RemovePiece());

                    RookOriginCol > RookDestCol ? status.SetLastColRookMove(piece->GetColor()) : status.SetFirstColRookMove(piece->GetColor());
                    status.SetKingMove(piece->GetColor());
                    return true;
                }
                default: break;
            }
            return false;
        }
    }
    return false;
}


int Board::GetEvaluation()
{
    int score = 0;
    for (auto &record : records)
    {
        int factor = record.first->GetColor() == PieceColor::BLACK ? 1 : -1;
        switch(record.first->GetType())
        {
            case PieceType::PAWN: score += factor * 10; break;
            case PieceType::KNIGHT: score += factor * 20; break;
            case PieceType::BISHOP: score += factor * 30; break;
            case PieceType::ROOK: score += factor * 30; break;
            case PieceType::QUEEN: score += factor * 100; break;
            case PieceType::KING: score += factor * 200; break;
        }

        // INFO("Piece: {0} - {1} | position = {2} - {3}", PieceTypeLog(record.first->GetType()), 
            //  PieceColorLog(record.first->GetColor()), record.second.first, record.second.second);
    }
    return score;
}

void Board::MakeMove(Move &move)
{
    Piece* piece = move.GetMovedPiece();
    auto start = move.GetOriginPos();
    auto end = move.GetDestinationPos();

    {
        MoveState moveState;
        moveState.moved = piece;
        moveState.start = start;
        moveState.end = end;
        moveState.type = move.GetType();
        moveState.captured = move.GetCapturedPiece();
        moveHistory.push(moveState);
    }
        
    switch(move.GetType())
    {
        case(MoveType::NORMAL):
        {
            m_Grid.GetSquare(end.first, end.second)->SetOccupied(m_Grid.GetSquare(start.first, start.second)->RemovePiece());
            break;
        }
        case(MoveType::CAPTURE):
        {
            m_Grid.GetSquare(end.first, end.second)->RemovePiece();
            m_Grid.GetSquare(end.first, end.second)->SetOccupied(m_Grid.GetSquare(start.first, start.second)->RemovePiece());
            records[piece] = {end.first, end.second};
            records.erase(move.GetCapturedPiece());
            break;
        }
        case MoveType::CASTLING:
        {
            int RookOriginCol = ((end.second < start.second) ? MIN_COL_INDEX : MAX_COL_INDEX);
            int RookDestCol = ((end.second < start.second) ? start.second - 1 : start.second + 1);
            
            m_Grid.GetSquare(end.first, end.second)->SetOccupied(m_Grid.GetSquare(start.first, start.second)->RemovePiece());
            m_Grid.GetSquare(end.first, RookDestCol)->SetOccupied(m_Grid.GetSquare(start.first, RookOriginCol)->RemovePiece());    
        }
    }
}

void Board::UndoMove()
{
    if (moveHistory.empty())
        return;

    MoveState last = moveHistory.top();
    moveHistory.pop();

    // INFO("Piece: {0} - {1} | start = {2} - {3} | end = {4} - {5}", PieceTypeLog(last.moved->GetType()), 
    //      PieceColorLog(last.moved->GetColor()), last.start.first, last.start.second, last.end.first, last.end.second);

    // Normal (include castling move of king)
    m_Grid.GetSquare(last.start.first, last.start.second)->SetOccupied(
        m_Grid.GetSquare(last.end.first, last.end.second)->RemovePiece()
    );
    records[last.moved] = {last.start.first, last.start.second};

    // Capture
    if (last.captured != nullptr) 
    {
        m_Grid.GetSquare(last.end.first, last.end.second)->SetOccupied(last.captured);
        records[last.captured] = {last.end.first, last.end.second};
    }

    // Castling
    if (last.type == MoveType::CASTLING) 
    {
        int RookDestCol = ((last.end.second < last.start.second) ? last.start.second - 1 : last.start.second + 1);
        int RookOriginCol = ((last.end.second < last.start.second) ? MIN_COL_INDEX : MAX_COL_INDEX);

        m_Grid.GetSquare(last.start.first, RookOriginCol)->SetOccupied (
            m_Grid.GetSquare(last.start.first, RookDestCol)->RemovePiece()
        );
        records[m_Grid.GetSquare(last.start.first, RookOriginCol)->GetPiece()] = {last.start.first, RookOriginCol};
    }
}