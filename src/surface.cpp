#include <stdexcept>
#include "surface.hpp"

void throw_error(std::string funcname, GLenum success)
{
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

namespace dimanari
{
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
}