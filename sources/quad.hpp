#pragma once

#include "model.hpp"
#include "texture.hpp"
#include <memory>

class Quad: public OpenGLModel {
public:
    Quad(std::shared_ptr<Texture> texture);
    OpenGLModelType type() override;
};
