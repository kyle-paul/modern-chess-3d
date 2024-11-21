#include "Core/Render/Framebuffer.h"
#include "Core/Render/RendererAPI.h"
#include "Backends/OpenGL/OpenGLFramebuffer.h"

std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferConfig& spec)
{
    switch(RendererAPI::GetCurrentAPI()) 
    {
        case RendererAPI::API::None: 
        {
            ASSERT(false, "[Frame Buffer] None API backend is not supported.");
            return nullptr;
        }
        case RendererAPI::API::OpenGL: 
        {
            return std::make_shared<OpenGLFramebuffer>(spec);
        }
    }
    ASSERT(false, "[Frame Buffer] Please select an API backend for rendering. Options are [OpenGL, Vulcan]");
    return  nullptr;
}