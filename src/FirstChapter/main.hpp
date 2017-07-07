#ifndef MAIN_HPP
#define MAIN_HPP
#define STB_IMAGE_IMPLEMENTATION
#include "Utils.hpp"
#include "Precompiled.hpp"

// Cross platform specific utility defines

struct ShaderPart {
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
};

struct VertexBufferPart {
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
};

#endif // MAIN_HPP