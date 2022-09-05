#ifndef DIMA_PROJ_SHADER_HPP
#define DIMA_PROJ_SHADER_HPP
#include "GL_include.hpp"
#include <string>
#include <vector>

namespace dimanari
{
class Shader
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	// use/activate the shader
	void use();
	static void unuse();
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;  
	void setInt(const std::string &name, int value) const;   
	void setFloat(const std::string &name, float value) const;
	void setFloat2(const std::string &name, float valx, float valy) const;
	void setFloat2(const std::string &name, const glm::vec2 _vec2) const;
	void setFloat3(const std::string &name, float valx, float valy, float valz) const;
	void setFloat3(const std::string &name, const glm::vec3 _vec3) const;
	void setMatrixF4(const std::string &name, const glm::mat4& matr, bool transpose = GL_FALSE) const;
	~Shader();
	bool isActive();
protected:
	void Premake(const char* vertexPath, const char* fragmentPath, unsigned int &vertex, unsigned int &fragment);
	void Link(unsigned int &vertex, unsigned int &fragment);
	Shader() {}
private:
	Shader(const Shader& other) {}
	Shader& operator=(const Shader& other) { return *this; }
	static unsigned int last_ID;
};

class ShaderVBO : public Shader
{
public:
	ShaderVBO(const char* vertexPath, const char* fragmentPath);
	int BindBuffer(void *buffer, size_t total_size, size_t line_size, std::vector<size_t> elements_in_segment, GLenum usage);
	void DrawBoundArray(GLenum mode, GLint first);
	void DrawBoundArrayInst(GLenum mode, GLint first, size_t instances);
	~ShaderVBO();
private:
	unsigned int VBO, VAO;
	size_t last_bound_size;
};

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void BindBuffer(void *buffer, size_t lines, size_t line_size, std::vector<size_t> elements_in_segment, GLenum usage);
	unsigned int GetBuffer();
private:
	size_t m_line_size;
	size_t m_lines;
	unsigned int instanceVBO;
};

inline unsigned int VertexBuffer::GetBuffer()
{
	return instanceVBO;
}


inline bool Shader::isActive()
{
	return ID == last_ID;
}

}
#endif //!DIMA_PROJ_SHADER_HPP
