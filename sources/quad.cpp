#include "quad.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Quad::Quad() {
    mPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    glGenVertexArrays(1, &mID);
    glBindVertexArray(mID);

    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    float textures[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
    };

    glGenBuffers(1, &mVerticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &mTexturesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mTexturesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
}

Quad::~Quad() {
    glDeleteVertexArrays(1, &mID);
    glDeleteBuffers(1, &mVerticesVBO);
    glDeleteBuffers(1, &mTexturesVBO);
}

void Quad::draw(GLuint modelLocation) {
    glBindVertexArray(mID);
    glm::mat4 model;
    model = glm::translate(model, mPosition);
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Quad::setPosition(glm::vec3 position) {
    mPosition = position;
}
