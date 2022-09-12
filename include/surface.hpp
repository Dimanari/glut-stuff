#ifndef DIMA_PROJ_SURFACE_HPP
#define DIMA_PROJ_SURFACE_HPP
#include "texture.hpp"
#include "framebuf.hpp"
namespace dimanari
{
class Surface
{
public:
	Surface(GLsizei width, GLsizei height);
	~Surface();
	void Bind();
	static void Unbind();
	Texture& getTexture() { return m_texture; }
private:
	ShadowTexture m_texture;
	FrameBuf m_frame;
	RenderBuf m_rend;
	GLsizei m_width;
	GLsizei m_height;
};
}
#endif //!DIMA_PROJ_SURFACE_HPP