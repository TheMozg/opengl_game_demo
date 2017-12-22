#include "octahedron.hpp"

Octahedron::Octahedron(std::shared_ptr<Texture> texture): OpenGLModel(texture) {

  std::vector<float> vCoordinates = {
    0.0f, 0.0f, 0.1f,
    -0.1f, -0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,
  
    0.0f, 0.0f, -0.1f,
    -0.1f, -0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,

    0.0f, 0.0f, 0.1f,
    -0.1f, 0.1f, 0.0f,
    -0.1f, -0.1f, 0.0f,

    0.0f, 0.0f, -0.1f,
    -0.1f, 0.1f, 0.0f,
    -0.1f, -0.1f, 0.0f,

    0.0f, 0.0f, 0.1f,
    0.1f, 0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,

    0.0f, 0.0f, -0.1f,
    0.1f, 0.1f, 0.0f,
    0.1f, -0.1f, 0.0f,

    0.0f, 0.0f, 0.1f,
    -0.1f, 0.1f, 0.0f,
    0.1f, 0.1f, 0.0f,

    0.0f, 0.0f, -0.1f,
    -0.1f, 0.1f, 0.0f,
    0.1f, 0.1f, 0.0f,

  };
  
  std::vector<float> tCoordinates = {
    0.0f, 0.0f,
    0.1f, 0.0f,
    0.1f, 0.1f,
    
    0.0f, 0.0f,
    0.1f, 0.0f,
    0.1f, 0.1f,

    0.0f, 0.0f,
    0.1f, 0.0f,
    0.1f, 0.1f,
    
    0.0f, 0.0f,
    0.1f, 0.0f,
    0.1f, 0.1f,

    0.0f, 0.0f,
    0.1f, 0.0f,
    0.1f, 0.1f,
    
    0.0f, 0.0f,
    0.1f, 0.0f,
    0.1f, 0.1f,
  
  };
  initVBO(vCoordinates, tCoordinates);
}

OpenGLModelType Octahedron::type() {
    return OpenGLModelType::Octahedron;
}

bool Octahedron::collidesWith(glm::vec3 point, float offset) {
    glm::vec2 offsetVec2(offset, offset);
    return collidesWith(point, offsetVec2, offsetVec2, offsetVec2);
}

bool Octahedron::collidesWith(glm::vec3 point, glm::vec2 xoffset, glm::vec2 yoffset, glm::vec2 zoffset) {
    return (point.x >= mPosition.x - (0.1 + xoffset.x) && point.x <= mPosition.x + (0.1 + xoffset.y)) &&
           (point.y >= mPosition.y - (0.1 + yoffset.x) && point.y <= mPosition.y + (0.1 + yoffset.y)) &&
           (point.z >= mPosition.z - (0.1 + zoffset.x) && point.z <= mPosition.z + (0.1 + zoffset.y));
}
