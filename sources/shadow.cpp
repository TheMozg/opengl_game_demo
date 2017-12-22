#include "shadow.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ShadowCubeMap::ShadowCubeMap() {
    mProjection = glm::perspective(glm::radians(90.0f), (float)1024 / (float)1024, 1.0f, 25.0f);
    glGenTextures(1, &mID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mID);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

ShadowCubeMap::~ShadowCubeMap() {
    glDeleteTextures(1, &mID);
}

glm::vec3 ShadowCubeMap::getPosition() {
    return mPosition;
}

void ShadowCubeMap::setPosition(glm::vec3 position) {
    mPosition = position;
    mTransforms.clear();
    mTransforms.push_back(mProjection * glm::lookAt(mPosition, mPosition + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    mTransforms.push_back(mProjection * glm::lookAt(mPosition, mPosition + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    mTransforms.push_back(mProjection * glm::lookAt(mPosition, mPosition + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
    mTransforms.push_back(mProjection * glm::lookAt(mPosition, mPosition + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
    mTransforms.push_back(mProjection * glm::lookAt(mPosition, mPosition + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
    mTransforms.push_back(mProjection * glm::lookAt(mPosition, mPosition + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
}

std::vector<glm::mat4> ShadowCubeMap::getTransforms() {
    return mTransforms;
}

void ShadowCubeMap::activate() {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mID);
    glActiveTexture(GL_TEXTURE0);
}
