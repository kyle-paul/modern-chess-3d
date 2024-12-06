#include "Core/Render/Texture.h"
#include "Backends/OpenGL/OpenGLTexture2D.h"
#include "Core/Render/RendererAPI.h"
#include "Core/Debug/Assert.h"

std::shared_ptr<Texture2D> Texture2D::Create(const std::string &path)
{
    switch(RendererAPI::GetCurrentAPI())
    {
        case RendererAPI::API::None: 
        {
            ASSERT(false, "[Texture] The Renderer API is not specified. OpenGL is used by default");
            return nullptr;
        }
        case RendererAPI::API::OpenGL:
        {
            return std::make_shared<OpenGLTexture2D>(path);
        }
    }
    ASSERT(false, "[Texture] Please select an API backend for rendering. Options are [OpenGL, Vulcan]");
    return  nullptr;
}

std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
    switch(RendererAPI::GetCurrentAPI())
    {
        case RendererAPI::API::None: 
        {
            ASSERT(false, "[Texture] The Renderer API is not specified. OpenGL is used by default");
            return nullptr;
        }
        case RendererAPI::API::OpenGL:
        {
            return std::make_shared<OpenGLTexture2D>(width, height);
        }
    }
    ASSERT(false, "[Texture] Please select an API backend for rendering. Options are [OpenGL, Vulcan]");
    return  nullptr;
}