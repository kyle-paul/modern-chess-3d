#pragma once
#include <memory>
#include "Core/Debug/Assert.h"

struct FramebufferConfig
{
	unsigned int Width, Height;
	unsigned int Samples = 1;
	bool SwapChainTarget = false;
};

class Framebuffer
{
public:
	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	virtual unsigned int GetColorAttachmentID() const = 0;
	virtual const FramebufferConfig& GetSpecification() const = 0;

	virtual const unsigned int GetWidth() const = 0;
	virtual const unsigned int GetHeight() const = 0;
	virtual void Resize(uint32_t width, uint32_t height) = 0;

	static std::shared_ptr<Framebuffer> Create(const FramebufferConfig& spec);
};
