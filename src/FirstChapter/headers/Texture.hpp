#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Utils.hpp"

#include <glad/glad.h>
#include <glm.hpp>

#include <string>
#include <optional>
#include <iostream>

class Texture {
public:
    const unsigned int ID;

    Texture(const std::string& path);

    void SetActive();
};


#endif