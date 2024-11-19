#pragma once
#include "Core/Render/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void UnBind() const override;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer) override;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer) override;

    virtual const std::shared_ptr<VertexBuffer> GetVertexBuffer() const override { return m_VertexBuffer; }
    virtual const std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }
    virtual const uint32_t GetVAID() const override { return VAO; }

private:
    uint32_t VAO;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};