#ifndef MAIN_HPP
#define MAIN_HPP
#include "Precompiled.hpp"
#include "Utils.hpp"
#include "Shader.hpp"
#include "camera.hpp"
#include "Texture.hpp"
#include "Material.hpp"
#include "Model.hpp"
#include "SurfaceExtraction.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#define cauto const auto

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