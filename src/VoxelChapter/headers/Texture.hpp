#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Utils.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <optional>
#include <iostream>
#include <array>

class Texture {
public:
    const unsigned int ID;

    Texture(const std::string& path);

    void SetActive();
};

struct Cubemap {
    const unsigned int ID;

    static Cubemap create(const std::array<std::string, 6>& texturePaths);

    static void use(Cubemap& cubemap);
};


#endif