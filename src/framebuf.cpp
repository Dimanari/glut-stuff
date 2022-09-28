#include "controller.hpp"
#include "framebuf.hpp"
namespace dimanari
{
FrameBuf::FrameBuf() : fbo(0)
{
	glGenFramebuffers(1, &fbo);
}
FrameBuf::~FrameBuf()
{
	glDeleteFramebuffers(1, &fbo);
}
void FrameBuf::GetTexture(Texture* mTexture, GLenum attachment)
{
	Bind();

	glBindTexture(GL_TEXTURE_2D, mTexture->Data());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, mTexture->Data(), 0);
}

void FrameBuf::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}
void FrameBuf::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

RenderBuf::RenderBuf(GLenum format, GLsizei width, GLsizei height) : rbo(0)
{
	glGenRenderbuffers(1, &rbo);
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}
RenderBuf::~RenderBuf()
{
	glDeleteRenderbuffers(1, &rbo);
}
void RenderBuf::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
}
void RenderBuf::Unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
void RenderBuf::Attach(GLenum attachment)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo);
}
}