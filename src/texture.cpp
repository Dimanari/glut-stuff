#include <stdio.h> /* fread fopen fclose */
#ifdef __STDC_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#else
int memcpy_s(void *dest, size_t destsz, const void *src, size_t count );
#endif
#include <string.h> /* memcpy_s */
#include <stdexcept> /* runtime error */
#include "texture.hpp"

namespace dimanari
{
Texture::Texture(const char *path, bool flip_y)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;

	FILE * file = fopen(path,"rb");
	if (!file)
	{
		throw std::runtime_error("Image could not be opened");
	}

	// Read the header, i.e. the 54 first bytes
	VerifyBMP(header, file);

	// Read the information about the image
	dataPos		= *(int*)&(header[0x0A]);
	imageSize	= *(int*)&(header[0x22]);
	m_w			= *(int*)&(header[0x12]);
	m_h			= *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (0 == imageSize)
	{
		imageSize= m_w * m_h * 3; // 3 : one byte for each Red, Green and Blue component
	}
	if (0 == dataPos)
	{
		dataPos = 54; // The BMP header is done that way
	}

	// Create a buffer
	m_data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(m_data,1,imageSize,file);

	// Everything is in memory now, the file wan be closed
	fclose (file);

	if (flip_y)
	{
		// swap y-axis
		unsigned char * tmpBuffer = new unsigned char[m_w * 3];
		unsigned int size = m_w * 3;
		for (unsigned int i = 0; i < (m_h / 2); ++i)
		{
			// copy row i to tmp
			memcpy_s(tmpBuffer, size, m_data + m_w * 3 * i, size);
			// copy row h-i-1 to i
			memcpy_s(m_data + m_w * 3 * i, size, m_data + m_w * 3 * (m_h - i - 1), size);
			// copy tmp to row h-i-1
			memcpy_s(m_data + m_w * 3 * (m_h - i - 1), size, tmpBuffer, size);
		}
		delete [] tmpBuffer;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_w, m_h, 0, GL_BGR, GL_UNSIGNED_BYTE, m_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	delete [] m_data;
	m_data = NULL;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::VerifyBMP(unsigned char *header, FILE* file)
{
	// If less than 54 byes are read, problem
	if ( 54 != fread(header, 1, 54, file))
	{
		throw std::runtime_error("Not a correct BMP file");
	}
	// A BMP files always begins with "BM"
	if ('B' != header[0] || 'M' != header[1])
	{
		throw std::runtime_error("Not a correct BMP file");
	}
	// Make sure this is a 24bpp file
	if ( 0 != *(int*)&(header[0x1E]))
	{
		throw std::runtime_error("Not a correct BMP file");
	}
	if (24 != *(int*)&(header[0x1C]) )
	{
		int temp = *(int*)&(header[0x1C]);
		throw std::runtime_error("Not a correct BMP file");
	}
}

Texture::Texture() : m_h(0), m_w(0), m_texture(0)
{}

}
#ifndef __STDC_LIB_EXT1__
int memcpy_s(void *dest, size_t destsz, const void *src, size_t count )
{
	memcpy(dest, src, count);
	return 0;
}
#endif