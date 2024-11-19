#pragma once
#include "Core/Render/Buffer.h"

// ============ Vertex Buffer ============
class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(float *vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer() override;

    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void SetData(const void *data, uint32_t size) override;

    virtual void SetLayout(const BufferLayout &layout) override 
    {
        m_BufferLayout = layout;
    }
    
    virtual const BufferLayout& GetLayout() const override 
    {
        return m_BufferLayout;
    }
    
    virtual const uint32_t GetSize() const override { return m_BufferSize; }

private:
    uint32_t VBO;
    BufferLayout m_BufferLayout;
    uint32_t m_BufferSize;
};

// ============ Index Buffer ============ 
class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
    virtual ~OpenGLIndexBuffer() override;

    virtual uint32_t GetCount() const { return m_VertexCount; } 
    virtual void Bind() const override;
    virtual void Unbind() const override;
private:
    uint32_t IBO;
    uint32_t m_VertexCount;
};