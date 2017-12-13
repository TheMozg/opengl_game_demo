#pragma once

#include "opengl.hpp"

#include <glad/glad.h>
#include <string>

class Texture: public OpenGLObject {
public:
    Texture();
	Texture(std::string const &filename);
    ~Texture();

    void load(std::string const &filename);
    void activate();
};
