#pragma once

#include "opengl.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

class Quad: public OpenGLObject {
private:
    glm::vec3 mPosition;
    GLuint mVerticesVBO;
    GLuint mTexturesVBO;
public:
    Quad();
    ~Quad();

    void draw(GLuint modelLocation);
    void setPosition(glm::vec3 position);
};
