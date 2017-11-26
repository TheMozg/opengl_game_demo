#pragma once

#include <glad/glad.h>

#include <string>

class Shader
{
private:
	GLuint mID;
	GLuint create(std::string const &filename);
	void   print_errors(GLuint shader);
public:
     Shader();
	~Shader();

	GLuint getID();
	GLuint getUniformLocation(std::string const &name);
	
	void   activate();
    void   deactivate();
	void   destroy();

	void   attach(std::string const &filename);
	void   link();
};