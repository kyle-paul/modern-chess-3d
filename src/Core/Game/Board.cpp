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
    int firstrow, secondrow;
    switch(color)
    {
        case PieceColor::WHITE:
        {
            firstrow = MIN_ROW_INDEX;
            secondrow = MIN_ROW_INDEX + 1;
            break;
        }
        case PieceColor::BLACK:
        {
            firstrow = MAX_ROW_INDEX;
            secondrow = MAX_ROW_INDEX - 1;
            break;
        }
    }   

    int firstcol = MIN_COL_INDEX;

    for (int col=firstcol; col <= MAX_COL_INDEX; col++)
    {
        m_Grid.GetSquare(secondrow, col)->SetOccupied(new Piece(PieceType::PAWN, color));
    }

    // ROOK
	m_Grid.GetSquare(firstrow, firstcol)->SetOccupied(new Piece(PieceType::ROOK, color));
	m_Grid.GetSquare(firstrow, firstcol + 7)->SetOccupied(new Piece(PieceType::ROOK, color));

	// KNIGHT
	m_Grid.GetSquare(firstrow, firstcol + 1)->SetOccupied(new Piece(PieceType::KNIGHT, color));
	m_Grid.GetSquare(firstrow, firstcol + 6)->SetOccupied(new Piece(PieceType::KNIGHT, color));

	// BISHOP
	m_Grid.GetSquare(firstrow, firstcol + 2)->SetOccupied(new Piece(PieceType::BISHOP, color));
	m_Grid.GetSquare(firstrow, firstcol + 5)->SetOccupied(new Piece(PieceType::BISHOP, color));

	// QUEEN
	m_Grid.GetSquare(firstrow, firstcol + 3)->SetOccupied(new Piece(PieceType::QUEEN, color));

	// KING
	m_Grid.GetSquare(firstrow, firstcol + 4)->SetOccupied(new Piece(PieceType::KING, color));
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
    float z = 0.0f;
    float r, c;
    
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

                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(c, r, z)) *
                                  glm::scale(glm::mat4(1.0f), glm::vec3(0.014f, 0.014f, 0.014f));
                pieceShader->SetMat4("model", model);
                pieceShader->SetFloat3("light_direction", env.light_direction);

                switch(m_Grid.GetSquare(row, col)->GetPiece()->GetColor())
                {
                    case PieceColor::WHITE:
                    {
                        pieceShader->SetFloat3("v_color", glm::vec3(0.9f, 0.9f, 0.9f));
                        break;
                    }
                    case PieceColor::BLACK:
                    {
                        pieceShader->SetFloat3("v_color", glm::vec3(0.2f, 0.2f, 0.2f));
                        break;
                    }
                }

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

void Board::RenderMoveToSquare()
{

}

void Board::RenderValidMove()
{

}

bool Board::MovePlayer()
{
    return false;
}