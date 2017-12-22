#include "model.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

OpenGLModel::OpenGLModel(std::shared_ptr<Texture> texture) {
    mTexture = texture;
    glGenVertexArrays(1, &mID);
}

void OpenGLModel::initVBO(std::vector<float> &coordinates) {
    glBindVertexArray(mID);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(float), coordinates.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    mVertexCount = coordinates.size() / 8 * 3;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

OpenGLModel::~OpenGLModel() {
    glDeleteVertexArrays(1, &mID);
    glDeleteBuffers(1, &mVBO);
}

void OpenGLModel::draw(GLuint modelLocation) {
    mTexture->activate();
    glBindVertexArray(mID);
    glm::mat4 model;
    model = glm::translate(model, mPosition);
    model = glm::rotate(model, glm::radians(mRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
}

void OpenGLModel::move(glm::vec3 position) {
    mPosition = position;
}

void OpenGLModel::rotate(glm::vec3 angles) {
    mRotation = angles;
}
