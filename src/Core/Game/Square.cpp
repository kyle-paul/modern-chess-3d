#include "Core/Game/Square.h"
#include "Core/Render/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


Square::Square()
{

}

Square::~Square()
{

}

void Square::Init()
{
    SquareVA = VertexArray::Create();
    SquareVB = VertexBuffer::Create(vertices, sizeof(vertices));
    SquareVB->SetLayout({
        { ShaderDataType::Float3, "a_Position", false },
    });
    SquareVA->AddVertexBuffer(SquareVB);
}

int selectedRow = 0;
int selectedCol = 0;

void Square::Render(const std::shared_ptr<Shader> &square_shader)
{
    float r, c;
    for (int row=1; row <= 8; row++)
    {
        for (int col=1; col <= 8; col++)
        {
            r = 1.0 * (row - 5);
            c = 1.0 * (col - 5);

            if (row == selectedRow && col == selectedCol)
            {
            }

            else if ((row + col) & 1) 
            {
                square_shader->SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(r, c, 0.0f)));
                square_shader->SetInt("type", 1);
                Renderer::Draw(SquareVA, true, 4);
            }
            else if (row == 1 & col == 1)
            {
                square_shader->SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(r, c, 0.0f)));
                square_shader->SetInt("type", 2);
                Renderer::Draw(SquareVA, true, 4);
            }
            else
            {
                square_shader->SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(r, c, 0.0f)));
                square_shader->SetInt("type", 0);
                Renderer::Draw(SquareVA, true, 4);
            }
        }        
    }
}