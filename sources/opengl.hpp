#pragma once

#include <glad/glad.h>
#include <string>

class OpenGLObject {
protected:
    GLuint mID;
    void printError(std::string error);
public:
    OpenGLObject();

    // disable copy constructor and assignment
    OpenGLObject(const OpenGLObject&) = delete;
    void operator=(const OpenGLObject&) = delete;

    GLuint getID();
};
