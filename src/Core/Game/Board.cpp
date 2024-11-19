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
    m_Squares.Init();
    INFO("Chess Board loaded successfully");
}

const glm::mat4 Board::GetTransform() const
{
    return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation));
}

void Board::RenderChessBoard()
{
    Renderer::Draw(boardVA, true, 36);
}

void Board::RenderBoardSquares(const std::shared_ptr<Shader> &square_shader)
{
    m_Squares.Render(square_shader);
}

void Board::RenderChessPieces()
{

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