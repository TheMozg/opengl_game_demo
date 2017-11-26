#include "shader.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <iostream>

Shader::Shader()
{
	mID = glCreateProgram(); 
}

Shader::~Shader()
{
	destroy();
}

void Shader::activate()
{
	glUseProgram(mID); 
}

void Shader::deactivate()
{ 
	glUseProgram(0); 
}

GLuint Shader::getID() 
{
	return mID;
}

GLuint Shader::getUniformLocation(std::string const &name)
{
	return glGetUniformLocation(mID, name.c_str());
}

void Shader::destroy() 
{
	glDeleteProgram(mID); 
}

void Shader::attach(std::string const &filename)
{
	std::ifstream fd(filename);
	if (fd.fail())
	{
		std::cerr << "Error: could not open shader - " << filename << std::endl;
		return;
	}
	auto src = std::string(std::istreambuf_iterator<char>(fd),
		(std::istreambuf_iterator<char>()));

	const char * source = src.c_str();
	auto shader = create(filename);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		print_errors(shader);
	}

	glAttachShader(mID, shader);
	glDeleteShader(shader);
}

void Shader::link()
{
	glLinkProgram(mID);

	GLint status;
	glGetProgramiv(mID, GL_LINK_STATUS, &status);
	if (!status)
	{
		print_errors(mID);
	}
}

void Shader::print_errors(GLuint id)
{
	GLint length;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	std::unique_ptr<char[]> buffer(new char[length]);
	glGetShaderInfoLog(id, length, nullptr, buffer.get());
	std::cerr << "Error: " << buffer.get() << std::endl;
}

GLuint Shader::create(std::string const &filename)
{
	auto idx = filename.rfind(".");
	auto ext = filename.substr(idx + 1);
	if (ext == "comp") return glCreateShader(GL_COMPUTE_SHADER);
	else if (ext == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
	else if (ext == "geom") return glCreateShader(GL_GEOMETRY_SHADER);
	else if (ext == "tcs")  return glCreateShader(GL_TESS_CONTROL_SHADER);
	else if (ext == "tes")  return glCreateShader(GL_TESS_EVALUATION_SHADER);
	else if (ext == "vert") return glCreateShader(GL_VERTEX_SHADER);
	else                    return false;
}
