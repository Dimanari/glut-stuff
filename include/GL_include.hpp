#ifndef DIMA_PROJ_GL_INCLUDE_HPP
#define DIMA_PROJ_GL_INCLUDE_HPP
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <freeglut.h>
#include <freeglut_ext.h>
#include <freeglut_std.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <string>

namespace dimanari
{
	void throw_error(std::string funcname, GLenum success);
}
#endif //!DIMA_PROJ_GL_INCLUDE_HPP