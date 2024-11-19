#include <memory>

#include "Core/Game/Game.h"
#include "Core/Debug/Logging.h"
#include "Core/Render/Renderer.h"

float vertices[36 * 6] = {
    // Base of the chessboard
    -5.0, -5.0, 0.0, 0.55, 0.24, 0.09,
    -5.0,  5.0, 0.0, 0.55, 0.24, 0.09,
     5.0,  5.0, 0.0, 0.55, 0.24, 0.09,
     5.0, -5.0, 0.0, 0.55, 0.24, 0.09,

    // Top of the chessboard
    -4.0, -4.0, 0.5, 0.803, 0.522, 0.247,
    -4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
    -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
    -4.0,  4.0, 0.5, 0.803, 0.522, 0.247,

    -4.0,  4.0, 0.5, 0.803, 0.522, 0.247,
    -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
     4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
     4.0,  4.0, 0.5, 0.803, 0.522, 0.247,

     4.0,  4.0, 0.5, 0.803, 0.522, 0.247,
     4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
     4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
     4.0, -4.0, 0.5, 0.803, 0.522, 0.247,

     4.0, -4.0, 0.5, 0.803, 0.522, 0.247,
     4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
    -4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
    -4.0, -4.0, 0.5, 0.803, 0.522, 0.247,

    // Sides of the chessboard
    -4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
    -5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
    -5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
    -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,

    -4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
    -5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
     5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
     4.5,  4.5, 0.5, 0.545, 0.271, 0.075,

     4.5,  4.5, 0.5, 0.545, 0.271, 0.075,
     5.0,  5.0, 0.0, 0.35, 0.15, 0.06,
     5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
     4.5, -4.5, 0.5, 0.545, 0.271, 0.075,

     4.5, -4.5, 0.5, 0.545, 0.271, 0.075,
     5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
    -5.0, -5.0, 0.0, 0.35, 0.15, 0.06,
    -4.5, -4.5, 0.5, 0.545, 0.271, 0.075
};

unsigned int indices[36] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15,
    16, 17, 18, 19,
    20, 21, 22, 23,
    24, 25, 26, 27,
    28, 29, 30, 31,
    32, 33, 34, 35
};

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::Init()
{
    shadlib.Load("board_shader", "assets/shaders/BoardShader.glsl");
    INFO("Shader {0} loaded successfully", shadlib.Get("board_shader")->GetName());

    boardVA = VertexArray::Create();
    boardVB = VertexBuffer::Create(vertices, sizeof(vertices));
    boardVB->SetLayout({
        { ShaderDataType::Float3, "a_Position", false },
        { ShaderDataType::Float3, "a_Color",  false },
    });
    boardVA->AddVertexBuffer(boardVB);

    boardIB = IndexBuffer::Create(indices, 36);
    boardVA->SetIndexBuffer(boardIB);
    INFO("VAO & VBO & IBO {0} loaded successfully");   
}

void Game::Run(Environment &env)
{
    shadlib.Get("board_shader")->Bind();
    shadlib.Get("board_shader")->SetMat4("projection_view", env.camera.GetProjectionViewMatrix());
    Renderer::Draw(boardVA);
}