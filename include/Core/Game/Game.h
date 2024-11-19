#pragma once
#include "Core/Render/Shader.h"
#include "Core/Render/VertexArray.h"
#include "Core/Render/Buffer.h"
#include "Core/Window/WindowConfig.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Run(Environment &env);

private:
    ShaderLibrary shadlib;
    std::shared_ptr<VertexArray> boardVA;
    std::shared_ptr<VertexBuffer> boardVB;
    std::shared_ptr<IndexBuffer> boardIB;

    GLuint VAO, VBO, IBO;
}; 