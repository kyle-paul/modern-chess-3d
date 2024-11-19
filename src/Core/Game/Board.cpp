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
    INFO("Chess Board loaded successfully");   
}

void Board::RenderChessBoard()
{
    Renderer::Draw(boardVA, true, 36);
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