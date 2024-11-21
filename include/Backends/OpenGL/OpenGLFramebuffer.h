#include "Core/Render/Framebuffer.h"

class OpenGLFramebuffer : public Framebuffer
{
public:
    OpenGLFramebuffer(const FramebufferConfig& spec);
    virtual ~OpenGLFramebuffer();

    void Invalidate();
    virtual void Bind() override;
    virtual void Unbind() override;

    virtual unsigned int GetColorAttachmentID() const override { return m_ColorAttachment; }
    virtual const FramebufferConfig& GetSpecification() const override { return m_Specification; }

    virtual const unsigned int GetWidth() const { return m_Specification.Width; }   
	virtual const unsigned int GetHeight() const { return m_Specification.Height; }
    virtual void Resize(uint32_t width, uint32_t height) override;

private:
    unsigned int m_RendererID;
    unsigned int m_ColorAttachment, m_DepthAttachment;
    FramebufferConfig m_Specification;
};