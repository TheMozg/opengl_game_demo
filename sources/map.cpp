#include "map.hpp"

#include "quad.hpp"
#include "cube.hpp"
#include <stb_image.h>
#include <string>
#include <iostream>

std::list<std::unique_ptr<OpenGLModel>> Map::load(std::string const &filename, std::vector<std::shared_ptr<Texture>> textures) {
    std::list<std::unique_ptr<OpenGLModel>> objects;
    stbi_set_flip_vertically_on_load(false);
    int width, height, channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 3);
    if (data) {
        unsigned int elevationMap[256][256];
        unsigned int textureMap[256][256];
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                elevationMap[i][j] = data[(i*width + j) * 3] / 32;
                textureMap[i][j] = data[(i*width + j) * 3 + 1] / 128;
            }
        }
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                // floor up to elevation
                for (size_t e = 0; e <= elevationMap[i][j]; e++) {
                    objects.push_back(std::make_unique<Cube>(textures[textureMap[i][j]]));
                    objects.back()->move(glm::vec3(j, e, i));
                }

                // ceiling
                objects.push_back(std::make_unique<Cube>(textures[2]));
                objects.back()->move(glm::vec3(j, 8, i));
            }
        }
    }
    else {
        std::cerr << "ERROR: Failed to load map - " << filename << std::endl;
    }
    stbi_image_free(data);
    return objects;
}
