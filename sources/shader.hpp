#pragma once

#include "opengl.hpp"

#include <glad/glad.h>
#include <string>

class Shader: public OpenGLObject {
private:
    GLuint create(std::string const &filename);
    void   printErrors(GLuint shader);
public:
    Shader();
    ~Shader();

    GLuint getUniformLocation(std::string const &name);
    void   activate();
    void   attach(std::string const &filename);
    void   link();
};
