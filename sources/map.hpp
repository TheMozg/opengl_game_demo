#pragma once

#include "model.hpp"

#include <glad/glad.h>
#include <string>
#include <list>
#include <vector>
#include <memory>

class Map {
public:
    static std::list<std::unique_ptr<OpenGLModel>> load(
        std::string const &filename, 
        std::vector<std::shared_ptr<Texture>> textures
    );
};
