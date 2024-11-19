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

#include <iostream>

void Renderer::Draw(const std::shared_ptr<VertexArray> &VA, const bool &isQuad, const uint32_t &count)
{
    VA->Bind();
    if (isQuad) glDrawArrays(GL_QUADS, 0, count);
    else glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::DrawIndexed(const std::shared_ptr<VertexArray> &VA)
{
    VA->Bind();
    glDrawElements(GL_TRIANGLES, VA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);    
}