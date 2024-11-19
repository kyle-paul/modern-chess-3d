#pragma once
#include <Core/Render/Shader.h>
#include "Core/Render/VertexArray.h"
#include "Core/Render/Buffer.h"

class Square
{
public:
    Square();
    ~Square();
    
    void Init();
    void Render(const std::shared_ptr<Shader> &square_shader);

private:
    float vertices [4 * 3] = {
        0.0f, 0.0f, 0.5f,
        0.0f, 1.0f, 0.5f,
        1.0f, 1.0f, 0.5f,
        1.0f, 0.0f, 0.5f,
    };
    
    std::shared_ptr<VertexArray> SquareVA;
    std::shared_ptr<VertexBuffer> SquareVB;
};