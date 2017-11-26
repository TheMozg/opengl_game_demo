#pragma once

#include <glad/glad.h>

#include <string>

class Texture
{
private:
	GLuint mID;
public:
	void init();
	void load(std::string const &filename);
	GLuint getID();
};