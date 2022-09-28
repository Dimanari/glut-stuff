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
	inline void Unbind();
	inline void ActivateCube(GLenum texture_num);
	inline void BindCube();

	inline void UnbindCube();
protected:
	Texture();
	void SetTexture(int texture);
	void SetDimensions(unsigned int w_,unsigned int h_);
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
	ShadowTexture() : Texture() {}
	int MakeTexture(unsigned int w_,unsigned int h_);
	int MakeDepthTexture(unsigned int w_,unsigned int h_);
	int MakeCubeTexture(unsigned int w_,unsigned int h_);
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


inline void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

inline void Texture::ActivateCube(GLenum texture_num)
{
	glActiveTexture(texture_num);
	throw_error("glActiveTexture", glGetError());
	BindCube();
}
inline void Texture::BindCube()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	throw_error("glBindTexture", glGetError());
}


inline void Texture::UnbindCube()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
}
#endif //!DIMA_PROJ_TEXTURE_HPP