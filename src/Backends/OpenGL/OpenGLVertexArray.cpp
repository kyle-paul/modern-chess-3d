#include <glad/glad.h>
#include "Backends/OpenGL/OpenGLVertexArray.h"

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &VAO);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &VAO);
}

void OpenGLVertexArray::Bind() const 
{
    glBindVertexArray(VAO);
}

void OpenGLVertexArray::UnBind() const 
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer)
{    
    glBindVertexArray(VAO);
    index_buffer->Bind();
    m_IndexBuffer = index_buffer;
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer)
{
    glBindVertexArray(VAO);
    vertex_buffer->Bind();

    const auto &layout = vertex_buffer->GetLayout();
    uint32_t index = 0; 

    for (auto &element : layout) 
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.GetDimCount(), 			      // The number of element on a row
                              ShaderDataTypeToOpenGLBaseType(element.Type),   // GLtype -> float
                              element.Normalized ? GL_TRUE : GL_FALSE,        // Normalized or not
                              layout.GetStride(),                             // The number of element on a row * 4 bytes 
                              (const void*)(uintptr_t)element.Offset);        // Offset
        index++;

        WARN("{0} - {1} - {2}", element.GetDimCount(), layout.GetStride(), element.Offset);
    }
}