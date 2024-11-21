#pragma once
#include <glad/glad.h>
#include "Core/Debug/Assert.h"
#include <iostream>

namespace Utils
{
    static GLenum ShaderTypeFromString(const std::string type)
    {
        if (type == "vertex")
        {
            return GL_VERTEX_SHADER;
        }
        else if (type == "fragment" || type == "pixel")
        {
            return GL_FRAGMENT_SHADER;
        }
        ASSERT(false, "Unknown shader type!");
        return 0;
    }  
};