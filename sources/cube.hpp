#pragma once

#include "model.hpp"
#include "texture.hpp"
#include <memory>

class Cube: public OpenGLModel {
public:
    Cube(std::shared_ptr<Texture> texture);
};
