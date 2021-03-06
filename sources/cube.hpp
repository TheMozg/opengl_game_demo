#pragma once

#include "model.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <memory>

class Cube: public OpenGLModel {
public:
    Cube(std::shared_ptr<Texture> texture);
    OpenGLModelType type() override;
    bool collidesWith(glm::vec3 point, float offset) override;
    bool collidesWith(glm::vec3 point, glm::vec2 xoffset, glm::vec2 yoffset, glm::vec2 zoffset) override;
};
