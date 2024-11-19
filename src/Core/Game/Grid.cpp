#include "Core/Game/Grid.h"
#include "Core/Render/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::Init()
{
    SquareVA = VertexArray::Create();
    SquareVB = VertexBuffer::Create(vertices, sizeof(vertices));
    SquareVB->SetLayout({
        { ShaderDataType::Float3, "a_Position", false },
    });
    SquareVA->AddVertexBuffer(SquareVB);

    pieces.Pawn.Init();
    pieces.Bishop.Init();
    pieces.Rook.Init();
    pieces.Knight.Init();
    pieces.Queen.Init();
    pieces.King.Init();
}

void Grid::Render(const std::shared_ptr<Shader> &gridShader, const GameState &state)
{
    float r, c;
    for (int row=1; row <= 8; row++)
    {
        for (int col=1; col <= 8; col++)
        {
            r = 1.0 * (row - 5);
            c = 1.0 * (col - 5);

            if (row == state.SelectedRow && col == state.SelectedCol)
            {
                gridShader->SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(r, c, 0.0f)));
                gridShader->SetInt("type", 2);
                Renderer::Draw(SquareVA, true, 4);
            }
            else if ((row + col) & 1) 
            {
                gridShader->SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(r, c, 0.0f)));
                gridShader->SetInt("type", 1);
                Renderer::Draw(SquareVA, true, 4);
            }
            else
            {
                gridShader->SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(r, c, 0.0f)));
                gridShader->SetInt("type", 0);
                Renderer::Draw(SquareVA, true, 4);
            }
        }        
    }
}

Square* Grid::GetSquare(int row, int col)
{
    return &m_Squares[row][col];
}