#include "Utils.hpp"

auto createShader(std::string& shaderSource, int type) {
    auto shader = glCreateShader(type);
    auto shaderString = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderString, nullptr);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) return std::make_optional(shader);
    else {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "error: " <<
            infoLog << std::endl;
        return std::optional<GLuint>{};
    }
}

auto createShaderProgramm(std::vector<unsigned int> shaders) {
    auto shaderProgram = glCreateProgram();
    for (auto shader : shaders) {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
    int success = false;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // Whatever happens we delete the shaders afterwards for safety reason
    for(auto& shader : shaders)
        glDeleteShader(shader);
    if (success)
        return std::make_optional(shaderProgram);
    else {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "error: " << infoLog << std::endl;
        return std::optional<GLuint>{};
    }
}

Shader::Shader(filesystem::path & vertexShaderPath, filesystem::path & fragmentPath)
{
    if (filesystem::exists(vertexShaderPath) && filesystem::exists(fragmentPath)) {
        auto vertexShaderCode = unwrapOptional(readCompleteFile(vertexShaderPath.generic_string()), "couldn't read vertex shader");
        auto fragmentShaderCode = unwrapOptional(readCompleteFile(fragmentPath.generic_string()), "couldn't read fragment shader");
        auto vertexShader = unwrapOptional(createShader(vertexShaderCode, GL_VERTEX_SHADER), "failed to create vertex shader");
        auto fragmentShader = unwrapOptional(createShader(fragmentShaderCode, GL_FRAGMENT_SHADER), "failed to create fragment shader");
        this->ID = unwrapOptional(createShaderProgramm(std::vector<GLuint>{ vertexShader, fragmentShader }), "failed to create shader program");
    }
    else
        throw std::exception("Path to shaders doesn't exist!");
    
}

void Shader::use()
{
    glUseProgram(this->ID);
}

void Shader::setBool(const std::string & name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

std::optional<std::string> readCompleteFile(std::string filename)
{
    auto file = std::ifstream(filename);
    if (file.is_open()) {
        auto res = std::string();
        file.seekg(0, std::ios::end);
        res.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        res.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();
        return std::make_optional(res);
    }
    else {
        file.close();
        return std::optional<std::string>{};
    }
}
