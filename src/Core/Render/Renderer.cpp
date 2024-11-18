#include "Core/Render/Renderer.h"
#include "Core/Render/RendererAPI.h"
#include "Backends/OpenGL/OpenGLRenderer.h"
#include "Core/Debug/Logging.h"

void Renderer::Init()
{
    switch(RendererAPI::GetCurrentAPI())
    {
        case RendererAPI::API::None:
        {
            WARN("The Renderer API is not specified. OpenGL is used by default");
        }

        case RendererAPI::API::OpenGL:
        {
            OpenGLRenderer::Init();
            break;
        }
    } 
}

void Renderer::Shutdown()
{
    
}