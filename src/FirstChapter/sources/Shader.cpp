#include "../headers/shader.hpp"
#include "..\..\..\deps\oglplus\shader.hpp"
using namespace std::experimental;

std::optional<GLuint> createShader(std::string shaderSource, int type) {
    auto shader = glCreateShader(type);
    auto shaderString = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderString, nullptr);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success)
        return shader;
    else {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "error: " <<
            infoLog << std::endl;
        return {};
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
    for (auto& shader : shaders)
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

void Shader::setMat4(const std::string & name, const glm::mat4 & value) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string & name, const glm::vec3 & value) const
{
    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::use(const Shader & shader)
{
    glUseProgram(shader.ID);
}
