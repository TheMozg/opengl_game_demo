#include "quad.hpp"

Quad::Quad(std::shared_ptr<Texture> texture): OpenGLModel(texture) {
    std::vector<float> vCoordinates = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f,  0.0f,
        0.5f,  -0.5f, 0.0f,
        0.5f,  0.5f,  0.0f,
        -0.5f, 0.5f,  0.0f,
        0.5f,  -0.5f, 0.0f
    };

    std::vector<float> tCoordinates = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f
    };

    initVBO(vCoordinates, tCoordinates);
}

OpenGLModelType Quad::type() {
    return OpenGLModelType::Cube;
}