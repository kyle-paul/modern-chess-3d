#include "Core/Render/Framebuffer.h"

class OpenGLFramebuffer : public Framebuffer
{
public:
    OpenGLFramebuffer(const FramebufferConfig& spec);
    virtual ~OpenGLFramebuffer();

    void Invalidate();
    virtual void Bind() override;
    virtual void Unbind() override;

    virtual unsigned int GetColorAttachmentID(unsigned int index = 0) const override { 
        ASSERT(index < m_ColorAttachments.size());
        return m_ColorAttachments[index]; 
    }
    virtual const FramebufferConfig& GetSpecification() const override { return m_Specification; }

    virtual const unsigned int GetWidth() const { return m_Specification.Width; }   
	virtual const unsigned int GetHeight() const { return m_Specification.Height; }

    virtual void Resize(unsigned int width, unsigned int height) override;
	virtual int ReadPixel(unsigned int index, int x, int y) const override;
    virtual void ClearAttachment(unsigned int index, int value) override;

private:
    unsigned int m_RendererID;
    FramebufferConfig m_Specification;

    std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
    FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

    std::vector<unsigned int> m_ColorAttachments;
    unsigned int m_DepthAttachment = 0;
};