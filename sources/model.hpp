#pragma once

#include "opengl.hpp"
#include "texture.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

enum class OpenGLModelType {
    Quad,
    Cube
};

class OpenGLModel: public OpenGLObject {
protected:
    std::shared_ptr<Texture> mTexture;
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    GLuint mVerticesVBO;
    GLuint mTexturesVBO;
    GLuint mVertexCount;
    void initVBO(std::vector<float> vertexCoords, std::vector<float> textureCoords);
public:
    OpenGLModel(std::shared_ptr<Texture> texture);
    ~OpenGLModel();

    virtual OpenGLModelType type() = 0;
    virtual bool collidesWith(glm::vec3 point, float offset) = 0;
    virtual bool collidesWith(glm::vec3 point, glm::vec2 xoffset, glm::vec2 yoffset, glm::vec2 zoffset) = 0;

    void draw(GLuint modelLocation);
    void move(glm::vec3 position);
    void rotate(glm::vec3 angles);
};
