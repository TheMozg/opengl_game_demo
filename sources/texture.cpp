#include "texture.hpp"

#include <stb_image.h>
#include <glad/glad.h>
#include <string>

Texture::Texture() {
    glGenTextures(1, &mID);
}

Texture::Texture(std::string const & filename) : Texture() {
    load(filename);
}

Texture::~Texture() {
    glDeleteTextures(1, &mID);
}

void Texture::load(std::string const &filename) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (data) {
        glBindTexture(GL_TEXTURE_2D, mID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        printError("Failed to load texture - " + filename);
    }
    stbi_image_free(data);
}

void Texture::activate() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mID);
}
