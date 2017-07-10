#include "../headers/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


auto loadTexture = [](const std::string& path) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
        return std::make_optional(texture);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        glDeleteTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, 0);
        return std::optional<GLuint>{};
    }
};

Texture::Texture(const std::string & path) : ID(unwrapOptional(loadTexture(path), "failed to load texture"))
{
    
}

void Texture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
