#pragma once
#include <memory>
#include "Core/Debug/Assert.h"

enum class FramebufferTextureFormat
{
	None = 0,
	RGBA8, 					 // Color
	RED_INTEGER,
	DEPTH24STENCIL8,		 // Depth/stencil
	Depth = DEPTH24STENCIL8  // Defaults
};

struct FramebufferTextureSpecification
{
	FramebufferTextureSpecification() = default;
	FramebufferTextureSpecification(FramebufferTextureFormat format)
		: TextureFormat(format) {}
	FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
};

struct FramebufferAttachmentSpecification
{
	FramebufferAttachmentSpecification() = default;
	FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
		: Attachments(attachments) {}
	std::vector<FramebufferTextureSpecification> Attachments;
};

struct FramebufferConfig
{
	unsigned int Width = 0, Height = 0;
	unsigned int Samples = 1;
	bool SwapChainTarget = false;

	FramebufferAttachmentSpecification Attachments;
};

class Framebuffer
{
public:
	virtual ~Framebuffer() = default;
	
	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	virtual unsigned int GetColorAttachmentID(unsigned int index = 0) const = 0;
	virtual const FramebufferConfig& GetSpecification() const = 0;

	virtual void Resize(unsigned int width, unsigned int height) = 0;
	virtual int ReadPixel(unsigned int index, int x, int y) const = 0;
	virtual void ClearAttachment(unsigned int index, int value) = 0;

	static std::shared_ptr<Framebuffer> Create(const FramebufferConfig& spec);
};
