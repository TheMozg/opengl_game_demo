#include "model.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

OpenGLModel::OpenGLModel(std::shared_ptr<Texture> texture) {
    mTexture = texture;
    glGenVertexArrays(1, &mID);
}

void OpenGLModel::initVBO(std::vector<float> vertexCoords, std::vector<float> textureCoords) {
    glBindVertexArray(mID);

    glGenBuffers(1, &mVerticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCoords.size() * sizeof(float), vertexCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    mVertexCount = vertexCoords.size();

    glGenBuffers(1, &mTexturesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mTexturesVBO);
    glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(float), textureCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
}

OpenGLModel::~OpenGLModel() {
    glDeleteVertexArrays(1, &mID);
    glDeleteBuffers(1, &mVerticesVBO);
    glDeleteBuffers(1, &mTexturesVBO);
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
