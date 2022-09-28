#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

/*
*/

#include "shader.hpp"
namespace dimanari
{
unsigned int Shader::last_ID = 0;
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	unsigned int vertex;
	unsigned int fragment;

	Premake(vertexPath, fragmentPath, vertex, fragment);

	Link(vertex, fragment);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	throw_error("before shader", glGetError());
	unsigned int vertex;
	unsigned int fragment;
	unsigned int geometry;

	Premake(vertexPath, vertex, GL_VERTEX_SHADER);
	Premake(geometryPath, geometry, GL_GEOMETRY_SHADER);
	Premake(fragmentPath, fragment, GL_FRAGMENT_SHADER);
    throw_error("After Premakes", glGetError());


	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, geometry);
	glAttachShader(ID, fragment);
    throw_error("After CreateProgram", glGetError());

	Link(vertexPath);
	glDeleteShader(vertex);
	glDeleteShader(geometry);
	glDeleteShader(fragment);
}

void Shader::Premake(const char* shader_path, unsigned int &shader_id, GLenum shader_type)
{
	std::string shaderCode;
	std::ifstream ShaderFile;


	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		// open files
		ShaderFile.open(shader_path);
		std::stringstream ShaderStream;
		// read file's buffer contents into streams
		ShaderStream << ShaderFile.rdbuf();
		// close file handlers
		ShaderFile.close();
		// convert stream into string
		shaderCode = ShaderStream.str();
	}
	catch(std::ifstream::failure& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << shader_path << std::endl;
		std::cerr << e.what() << std::endl;
	}
	const char* ShaderCode = shaderCode.c_str();

	int success;
	char infoLog[512];
	
	// vertex Shader
	shader_id = glCreateShader(shader_type);
    throw_error("glCreateShader type:" + std::to_string(shader_type), glGetError());
	glShaderSource(shader_id, 1, &ShaderCode, NULL);

	glCompileShader(shader_id);
	// print compile errors if any
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::CUSTOM::COMPILATION_FAILED " << shader_path <<"\n" << infoLog << std::endl;
	};
}

void Shader::Premake(const char* vertexPath, const char* fragmentPath, unsigned int &vertex, unsigned int &fragment)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ " << vertexPath << " or " << fragmentPath << std::endl;
		std::cerr << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	int success;
	char infoLog[512];
	
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);

	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED " << vertexPath <<"\n" << infoLog << std::endl;
	};

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);

	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED " << fragmentPath <<"\n" << infoLog << std::endl;
	}
	
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
}

void Shader::Link(unsigned int &vertex, unsigned int &fragment)
{
	Link();
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Link(const std::string &files)
{
	int success;
	char infoLog[512];
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << ((files.size()) ? ("\nin " + files) : ("")) << "\n" << infoLog << std::endl;
	}

}
// use/activate the shader
void Shader::use()
{
	if(last_ID == ID)
		return;
	glUseProgram(ID);
	last_ID = ID;
}

void Shader::unuse()
{
	glUseProgram(0);
	last_ID = 0;
}
// utility uniform functions
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat2(const std::string &name, float valx, float valy) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), valx, valy);
}

void Shader::setFloat2(const std::string &name,const glm::vec2 _vec2) const
{
	setFloat2(name , _vec2.x, _vec2.y);
}
void Shader::setFloat3(const std::string &name, float valx, float valy, float valz) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), valx, valy, valz);
}

void Shader::setFloat3(const std::string &name,const glm::vec3 _vec3) const
{
	setFloat3(name, _vec3.x, _vec3.y, _vec3.z);
}
void Shader::setMatrixF4(const std::string &name,const glm::mat4& matr, bool transpose) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, transpose, glm::value_ptr(matr) );
}
Shader::~Shader()
{
	glDeleteProgram(ID);
}

ShaderVBO::ShaderVBO(const char* vertexPath, const char* fragmentPath)
	: Shader(vertexPath, fragmentPath)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

ShaderVBO::ShaderVBO(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	: Shader(vertexPath, fragmentPath, geometryPath)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

ShaderVBO::~ShaderVBO()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

int ShaderVBO::BindBuffer(void *buffer, size_t total_size, size_t line_size, std::vector<size_t> elements_in_segment, GLenum usage)
{
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, total_size, buffer, usage);
	size_t my_offset = 0;
	for(GLuint index = 0;index < elements_in_segment.size(); ++index)
	{
		glVertexAttribPointer(index, elements_in_segment[index], GL_FLOAT, GL_FALSE, line_size * sizeof(float), (void*)(my_offset* sizeof(float)));
		glEnableVertexAttribArray(index);
		my_offset += elements_in_segment[index];
	}
	last_bound_size = total_size / (line_size * (sizeof(float)));
	return 0;
}

void ShaderVBO::DrawBoundArray(GLenum mode, GLint first)
{
	glBindVertexArray(VAO);
	glDrawArrays(mode, first, last_bound_size);
}

void ShaderVBO::DrawBoundArrayInst(GLenum mode, GLint first, size_t instances)
{
	glBindVertexArray(VAO);
	glDrawArraysInstanced(mode, first, last_bound_size, instances);
}

VertexBuffer::VertexBuffer()
{
	glGenVertexArrays(1, &instanceVBO);
}
VertexBuffer::~VertexBuffer()
{
	glDeleteVertexArrays(1, &instanceVBO);
}
void VertexBuffer::BindBuffer(void *buffer, size_t lines, size_t line_size, std::vector<size_t> elements_in_segment, GLenum usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, line_size, &buffer, usage);
	m_line_size = line_size;
	m_lines = lines;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}