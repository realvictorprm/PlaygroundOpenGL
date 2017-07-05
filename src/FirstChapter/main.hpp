#ifndef MAIN_HPP
#define MAIN_HPP
// std lib includes
#define _HAS_CXX17 1
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <fstream>
#include <string>
#include <optional>
#include <tuple>
#include <numeric>

// library includes
#include <glad\glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

// Cross platform specific utility defines

struct ShaderPart {
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
};

struct VertexBufferPart {
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
};

#endif // MAIN_HPP