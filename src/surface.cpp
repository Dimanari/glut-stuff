#include <stdexcept>
#include "surface.hpp"

namespace dimanari
{

void throw_error(std::string funcname, GLenum success)
{
	if(success == GL_NO_ERROR)
		return;
	switch(success)
	{
	case GL_INVALID_ENUM:
		throw std::runtime_error( funcname + " GL_INVALID_ENUM" );
		break;
	case GL_INVALID_VALUE:
		throw std::runtime_error( funcname + " GL_INVALID_VALUE" );
		break;
	case GL_INVALID_OPERATION:
		throw std::runtime_error( funcname + " GL_INVALID_OPERATION" );
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		throw std::runtime_error( funcname + " GL_INVALID_FRAMEBUFFER_OPERATION" );
		break;
	case GL_OUT_OF_MEMORY:
		throw std::runtime_error( funcname + " GL_OUT_OF_MEMORY" );
		break;
	case GL_STACK_UNDERFLOW:
		throw std::runtime_error( funcname + " GL_STACK_UNDERFLOW" );
		break;
	case GL_STACK_OVERFLOW:
		throw std::runtime_error( funcname + " GL_STACK_OVERFLOW" );
		break;
	default:
		throw std::runtime_error( funcname + " " + std::to_string(success) );
		break;
	}
}

Surface::Surface(GLsizei width, GLsizei height) :
	m_rend(GL_DEPTH_COMPONENT, width, height), m_width(width), m_height(height)
{
	m_texture.MakeTexture(width, height);
	m_frame.Bind();

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rend.Data());
	GLenum success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("glFramebufferRenderbuffer", success);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.Data(), 0);
	success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("glFramebufferTexture", success);
	}

	static GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};

	glDrawBuffers(1, DrawBuffers);
	success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("glDrawBuffers", success);
	}
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("FUCK the framebuf failed!!!");
}
Surface::~Surface()
{

}
void Surface::Bind()
{
	m_frame.Bind();
	glViewport(0,0,m_width,m_height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}
void Surface::Unbind()
{
	FrameBuf::Unbind();
}

DepthSurface::DepthSurface(GLsizei width, GLsizei height) :
	m_texture(), m_width(width), m_height(height)
{
	m_texture.MakeDepthTexture(width, height);
	m_frame.Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_texture.Data(), 0);
	GLenum success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("glFramebufferTexture2D", success);
	}
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("FUCK the framebuf failed!!!");
	Unbind();
}
DepthSurface::~DepthSurface()
{
}
void DepthSurface::Bind()
{
	m_frame.Bind();
	glCullFace(GL_FRONT);
	glViewport(0,0,m_width,m_height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}
void DepthSurface::Unbind()
{
	glCullFace(GL_BACK);
	FrameBuf::Unbind();
}

DepthCubeSurface::DepthCubeSurface(GLsizei width, GLsizei height) :
	m_width(width), m_height(height)
{
	GLenum success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("Runaway error", success);
	}
	m_texture.MakeCubeTexture(width, height);
	success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("MakeCubeTexture", success);
	}
	m_frame.Bind();
	success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("Bind", success);
	}
	m_texture.ActivateCube(GL_TEXTURE0);
	success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("ActivateCube", success);
	}
	for (GLint face = 0; face < 6; face++)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, m_texture.Data(), 0);
	}
	success = glGetError();
	if(GL_NO_ERROR != success)
	{
		throw_error("glFramebufferTexture", success);
	}
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("FUCK the framebuf failed!!!");
	Unbind();
	m_texture.UnbindCube();
}
DepthCubeSurface::~DepthCubeSurface()
{
}
void DepthCubeSurface::Bind()
{
	m_frame.Bind();
	glCullFace(GL_FRONT);
	glViewport(0,0,m_width,m_height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
	throw_error("DepthCubeSurface::Bind", glGetError());
}
void DepthCubeSurface::SetFace(int face)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, m_texture.Data(), 0);
	throw_error("SetFace", glGetError());
}

void DepthCubeSurface::AllFaces()
{
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_texture.Data(), 0);
	throw_error("glFramebufferTexture GL_DEPTH_ATTACHMENT", glGetError());
}

void DepthCubeSurface::Unbind()
{
	glCullFace(GL_BACK);
	FrameBuf::Unbind();
}
}