#pragma once

#include "model.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <memory>

class Cube: public OpenGLModel {
public:
    Cube(std::shared_ptr<Texture> texture);
    OpenGLModelType type() override;
    bool collidesWith(glm::vec3 point) override;
};
