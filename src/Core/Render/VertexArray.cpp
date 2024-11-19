#include "Core/Render/VertexArray.h"
#include "Core/Render/RendererAPI.h"
#include "Backends/OpenGL/OpenGLVertexArray.h"

std::shared_ptr<VertexArray> VertexArray::Create() 
{
    switch(RendererAPI::GetCurrentAPI())
    {
        case RendererAPI::API::None: 
        {
            ASSERT(false, "[Vertex Array] None API backend is not supported.");
            return nullptr;
        }
        case RendererAPI::API::OpenGL: 
        {
            return std::make_shared<OpenGLVertexArray>();
        }
    }
    ASSERT(false, "[Vertex Array] Please select an API backend for rendering. Options are [OpenGL, Vulcan, DirectX]");
    return  nullptr;
}