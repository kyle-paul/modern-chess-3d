#include "Core/Game/Grid.h"

Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::Init()
{
    m_Quad.Init();
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

            gridShader->SetInt("v_row", row);
            gridShader->SetInt("v_col", col);

            if (row == state.SelectedRow && col == state.SelectedCol)
            {
                if (GetSquare(row, col)->GetOccupiedState())
                {
                    if (GetSquare(row, col)->GetPiece()->GetColor() == state.TurnColor)
                    {
                        m_Quad.Render(gridShader, glm::vec3(c, r, 0.0f), 2);
                    }
                    else 
                    {
                        m_Quad.Render(gridShader, glm::vec3(c, r, 0.0f));
                    }
                }
            }
            else if ((row + col) & 1) 
            {
                m_Quad.Render(gridShader, glm::vec3(c, r, 0.0f), 1);
            }
            else
            {
                m_Quad.Render(gridShader, glm::vec3(c, r, 0.0f), 0);
            }           
        }        
    }
}

Square* Grid::GetSquare(int row, int col)
{
    return &m_Squares[row][col];
}