#ifndef SHADER_HPP
#define SHADER_HPP

// local includes, depending on utils
#include "Utils.hpp"

// library includes
#include <glad/glad.h>
#include <glm.hpp>
#include <../glm/matrix.hpp>
#include <../glm/gtc/type_ptr.hpp>

// std includes
#include <iostream>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(std::experimental::filesystem::path& vertexShaderPath, std::experimental::filesystem::path& fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string & name, float x, float y, float z) const;

    static void use(const Shader& shader);
};

#endif