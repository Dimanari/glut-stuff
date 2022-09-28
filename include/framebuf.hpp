#ifndef DIMA_PROJ_FRAMEBUF_HPP
#define DIMA_PROJ_FRAMEBUF_HPP
#include "GL_include.hpp"
#include "texture.hpp"
namespace dimanari
{
class FrameBuf
{
public:
	FrameBuf();
	~FrameBuf();
	void Bind();
	static void Unbind();
	void GetTexture(Texture* mTexture, GLenum attachment);
	unsigned int Data() const { return fbo; }
private:
	unsigned int fbo;
};

class RenderBuf
{
public:
	RenderBuf(GLenum format, GLsizei width, GLsizei height);
	~RenderBuf();
	void Bind();
	static void Unbind();
	void Attach(GLenum attachment);
	unsigned int Data() const { return rbo; }
private:
	unsigned int rbo;
};
}
#endif //!DIMA_PROJ_FRAMEBUF_HPP