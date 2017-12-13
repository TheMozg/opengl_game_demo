#include "map.hpp"

#include "quad.hpp"
#include "cube.hpp"
#include <stb_image.h>
#include <string>
#include <iostream>

void Map::load(std::string const &filename) {
    mTextures.push_back(std::make_shared<Texture>("textures/portal_black.png"));
    mTextures.push_back(std::make_shared<Texture>("textures/portal_white.jpg"));
    mTextures.push_back(std::make_shared<Texture>("textures/portal_white_2.jpg"));

    mObjects.clear();

    stbi_set_flip_vertically_on_load(false);
    int width, height, channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 3);
    if (data) {
        unsigned int elevation[256][256];
        unsigned int textures[256][256];
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                elevation[i][j] = data[(i*width + j) * 3] / 32;
                textures[i][j] = data[(i*width + j) * 3 + 1] / 128;
            }
        }
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                // floor up to elevation
                for (size_t e = 0; e <= elevation[i][j]; e++) {
                    mObjects.push_back(std::make_unique<Cube>(mTextures[textures[i][j]]));
                    mObjects.back()->move(glm::vec3(j, e, i));
                }

                // ceiling
                mObjects.push_back(std::make_unique<Cube>(mTextures[2]));
                mObjects.back()->move(glm::vec3(j, 8, i));
            }
        }
    }
    else {
        std::cerr << "ERROR: Failed to load map - " << filename << std::endl;
    }
    stbi_image_free(data);
}

void Map::draw(GLuint modelLocation) {
    for (auto& obj : mObjects) {
        obj->draw(modelLocation);
    }
}
