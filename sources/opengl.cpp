#include "opengl.hpp"

#include <iostream>

void OpenGLObject::printError(std::string error) {
    std::cerr << "ERROR: " << error << std::endl;
}

OpenGLObject::OpenGLObject() {
    mID = 0;
}

GLuint OpenGLObject::getID() {
    return mID;
}
