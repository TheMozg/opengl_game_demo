#pragma once

#include "opengl.hpp"

#include <glm/glm.hpp>
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

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setVec2(const std::string &name, const glm::vec2 &value);
    void setVec2(const std::string &name, float x, float y);
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setVec3(const std::string &name, float x, float y, float z);
    void setVec4(const std::string &name, const glm::vec4 &value);
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat);
    void setMat3(const std::string &name, const glm::mat3 &mat);
    void setMat4(const std::string &name, const glm::mat4 &mat);
};
