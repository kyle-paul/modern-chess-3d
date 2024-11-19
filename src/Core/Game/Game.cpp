#include "Core/Game/Game.h"
#include "Core/Render/Shader.h"
#include "Core/Debug/Logging.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init()
{
    ShaderLibrary shadlib;
    shadlib.Load("board_shader", "assets/shaders/BoardShader.glsl");
    INFO("Shader {0} loaded successfully", shadlib.Get("board_shader")->GetName());
}

void Game::Run()
{
    
}