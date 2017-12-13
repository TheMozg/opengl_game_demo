#pragma once

#include "model.hpp"

#include <glad/glad.h>
#include <string>
#include <list>
#include <vector>
#include <memory>


class Map {
private:
    std::list<std::unique_ptr<OpenGLModel>> mObjects;
    std::vector<std::shared_ptr<Texture>> mTextures;
public:
    void load(std::string const &filename);
    void draw(GLuint modelLocation);
};
