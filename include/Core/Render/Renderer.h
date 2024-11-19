#pragma once
#include "Core/Render/VertexArray.h"

class Renderer
{
public:
    static void Init();
    static void Shutdown();
    static void DrawIndexed(const  std::shared_ptr<VertexArray> &VA);
    static void Draw(const std::shared_ptr<VertexArray> &VA, const bool &isQuad, const uint32_t &count);
};