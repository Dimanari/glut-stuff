#ifndef DIMA_PROJ_TEXTURE_HPP
#define DIMA_PROJ_TEXTURE_HPP
#include "GL_include.hpp"
namespace dimanari
{
class Texture
{
public:
	Texture(const char *path, bool flip_y = false);
	~Texture();
	inline unsigned int Data();
	inline unsigned int Size();
	inline unsigned int Width();
	inline unsigned int Height();
	inline void Activate(GLenum texture_num);
protected:
	Texture();
private:
	void VerifyBMP(unsigned char *header, FILE* file);
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	unsigned char *m_data;
	unsigned int m_h;
	unsigned int m_w;
	unsigned int m_texture;
friend class DepthMap;
};

class ShadowTexture : public Texture
{
	public:
	ShadowTexture() {}
friend class DepthMap;
};

inline unsigned int Texture::Data()
{
	return m_texture;
}
inline unsigned int Texture::Size()
{
	return m_h * m_w;
}
inline unsigned int Texture::Width()
{
	return m_w;
}
inline unsigned int Texture::Height()
{
	return m_h;
}

inline void Texture::Activate(GLenum texture_num)
{
	glActiveTexture(texture_num);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
}
#endif //!DIMA_PROJ_TEXTURE_HPP