#include "shader.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <iostream>

Shader::Shader() {
    mID = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(mID);
}

void Shader::activate() {
    glUseProgram(mID);
}

GLuint Shader::getUniformLocation(std::string const &name) {
    return glGetUniformLocation(mID, name.c_str());
}

void Shader::attach(std::string const &filename) {
    std::ifstream fd(filename);
    if (fd.fail()) {
        printError("Could not open shader - " + filename);
        return;
    }
    auto src = std::string(std::istreambuf_iterator<char>(fd),
        (std::istreambuf_iterator<char>()));

    const char * source = src.c_str();
    auto shader = create(filename);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        printErrors(shader);
    }

    glAttachShader(mID, shader);
    glDeleteShader(shader);
}

void Shader::link() {
    glLinkProgram(mID);
    GLint status;
    glGetProgramiv(mID, GL_LINK_STATUS, &status);
    if (!status) {
        printErrors(mID);
    }
}

void Shader::printErrors(GLuint id) {
    GLint length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    std::unique_ptr<char[]> buffer(new char[length]);
    glGetShaderInfoLog(id, length, nullptr, buffer.get());
    printError(buffer.get());
}

GLuint Shader::create(std::string const &filename) {
    auto idx = filename.rfind(".");
    auto ext = filename.substr(idx + 1);
    if (ext == "comp") return glCreateShader(GL_COMPUTE_SHADER);
    else if (ext == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
    else if (ext == "geom") return glCreateShader(GL_GEOMETRY_SHADER);
    else if (ext == "tcs")  return glCreateShader(GL_TESS_CONTROL_SHADER);
    else if (ext == "tes")  return glCreateShader(GL_TESS_EVALUATION_SHADER);
    else if (ext == "vert") return glCreateShader(GL_VERTEX_SHADER);
    else                    return false;
}

void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) {
    glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(mID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(mID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
