#pragma once

class RendererAPI
{
public:
    enum class API
    {
        None   = 0,
        OpenGL = 1,
        VulCan = 2,
    };

    inline static API GetCurrentAPI() { return m_API; }

private:
    static API m_API;  
};