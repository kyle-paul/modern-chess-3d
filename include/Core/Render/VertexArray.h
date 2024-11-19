#pragma once
#include <memory>
#include "Core/Render/Buffer.h"

class VertexArray
{
public:
    virtual ~VertexArray() {}
    
    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer) = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer) = 0;

    virtual const std::shared_ptr<VertexBuffer> GetVertexBuffer() const = 0;
    virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;
    virtual const uint32_t GetVAID() const = 0;

    static std::shared_ptr<VertexArray> Create();
};