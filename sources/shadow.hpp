#pragma once

#include "opengl.hpp"

#include <glm/glm.hpp>
#include <vector>

class ShadowCubeMap: public OpenGLObject {
protected:
    glm::vec3 mPosition;
    std::vector<glm::mat4> mTransforms;
    glm::mat4 mProjection;
public:
    ShadowCubeMap();
    ~ShadowCubeMap();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    std::vector<glm::mat4> getTransforms();
    void activate();
};
