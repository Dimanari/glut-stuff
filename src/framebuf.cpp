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

DepthMap::DepthMap(GLsizei width, GLsizei height, ShadowTexture &depth_map, void (*ShadowRender)())
{
	glGenTextures(1, &depth_map.m_texture);
	glBindTexture(GL_TEXTURE_2D, depth_map.m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
				width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

	depth_buffer.Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map.Data(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, width, height);
	depth_buffer.Bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	ShadowRender();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 2. then render scene as normal with shadow mapping (using depth map)
	glViewport(0, 0, Controller::GetW(), Controller::GetH());
}
DepthMap::~DepthMap()
{
}
}