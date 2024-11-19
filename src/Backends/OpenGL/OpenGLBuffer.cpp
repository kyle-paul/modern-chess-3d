#include "Backends/OpenGL/OpenGLBuffer.h"

// ============ Vertex Buffer ============
OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
    :m_BufferSize(size)
{
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() 
{
    glDeleteBuffers(1, &VBO);
}

void OpenGLVertexBuffer::Bind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void OpenGLVertexBuffer::Unbind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) 
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
} 


// ============ Index Buffer ============ 
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) 
    : m_VertexCount(count)
{
    glCreateBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &IBO);
}

void OpenGLIndexBuffer::Bind() const 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
}

void OpenGLIndexBuffer::Unbind() const 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}