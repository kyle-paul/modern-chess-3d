#include "Core/Render/Shader.h"
#include "Backends/OpenGL/OpenGLShader.h"
#include "Core/Render/RendererAPI.h"
#include "Core/Debug/Assert.h"

std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc) 
{
    switch(RendererAPI::GetCurrentAPI())
    {
        case RendererAPI::API::None: 
        {
            ASSERT(false, "[Shader] The Renderer API is not specified. OpenGL is used by default");
            return nullptr;
        }
        case RendererAPI::API::OpenGL:
        {
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }
    }
    ASSERT(false, "[Shader] Please select an API backend for rendering. Options are [OpenGL, Vulcan]");
    return  nullptr;
}

std::shared_ptr<Shader> Shader::Create(const std::string &name, const std::string& filepath) 
{
    switch(RendererAPI::GetCurrentAPI())
    {
        case RendererAPI::API::None: 
        {
            ASSERT(false, "The Renderer API is not specified. OpenGL is used by default");
            return nullptr;
        }
        case RendererAPI::API::OpenGL:
        {
            return std::make_shared<OpenGLShader>(name, filepath);
        }
    }
    ASSERT(false, "[Shader] Please select an API backend for rendering. Options are [OpenGL, Vulcan]");
    return  nullptr;
}


void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
    m_ShaderLib[name] = shader;
}

void ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    ASSERT(!Exists(name), "Shader already exists!");
    auto shader = Shader::Create(name, filepath); 
    Add(name, shader);
}

void ShaderLibrary::Load(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc)
{
    ASSERT(!Exists(name), "Shader already exists!");
    auto shader = Shader::Create(name, vertexSrc, fragmentSrc); 
    Add(name, shader);
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
{
    ASSERT(Exists(name), "Shader not found!");
    return m_ShaderLib[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
    return m_ShaderLib.find(name) != m_ShaderLib.end();
}