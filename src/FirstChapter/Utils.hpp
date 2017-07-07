#ifndef UTILS_HPP
#define UTILS_HPP
#include "Precompiled.hpp"
using namespace std::experimental;

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(filesystem::path& vertexShaderPath, filesystem::path& fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

template<typename T>
auto unwrapOptional(std::optional<T>& opt, const char* failMsg) {
    if (opt.has_value()) return opt.value();
    throw new std::exception(failMsg);
}

std::optional<std::string> readCompleteFile(std::string filename);


#endif