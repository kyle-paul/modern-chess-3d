#include "Core/Render/Quad.h"
#include "Core/Render/Renderer.h"

Quad::Quad()
{

}

Quad::~Quad()
{
    
}

void Quad::Init()
{
    QuadVA = VertexArray::Create();
    QuadVB = VertexBuffer::Create(vertices, sizeof(vertices));
    QuadVB->SetLayout({
        { ShaderDataType::Float3, "a_Position", false },
    });
    QuadVA->AddVertexBuffer(QuadVB);
}

void Quad::Render(const std::shared_ptr<Shader> &shad, const glm::vec3 &pos, const int &type)
{
    shad->SetMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z)));
    if (type!=-1) shad->SetInt("type", type);
    Renderer::Draw(QuadVA, true, 4);
}