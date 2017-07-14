#ifndef MODEL_HPP
#define MODEL_HPP

#ifndef _Texture_Type_Diffuse_Name
#define _Texture_Type_Diffuse_Name "texture_diffuse"
#endif
#ifndef _Texture_Type_Specular_Name
#define _Texture_Type_Specular_Name "texture_specular"
#endif

#include <vector>
#include <map>

#include <glm.hpp>
#include <glad/glad.h>
#include "Shader.hpp"

namespace Loader {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    enum class TextureType {
        Diffuse,
        Specular
    };

    struct TextureReference {
        uint32_t ID;
        TextureType type;

        static std::string typeAsString(const TextureReference& texture) {
            switch (texture.type) {
            case TextureType::Diffuse:
                return _Texture_Type_Diffuse_Name;
            case TextureType::Specular:
                return _Texture_Type_Specular_Name;
            };
        }
    };

    struct Mesh {
        const std::vector<Vertex> vertices;
        const std::vector<GLuint> indices;
        const std::vector<TextureReference> textures;
        const GLuint VAO, VBO, EBO;

        static Mesh create(std::vector<Vertex>& vertices, const std::vector<GLuint> indices, const std::vector<TextureReference> textures) {
            // create logic
            auto bufferSize = 2;
            auto buffers = new GLuint[bufferSize];
            GLuint VAO;
            auto VBO = buffers[0];
            auto EBO = buffers[1];
            glCreateVertexArrays(1, &VAO);
            glCreateBuffers(bufferSize, buffers);

            // Bind our VAO to which the VBO correspondends 
            glBindVertexArray(VAO);
            // Bind the VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // Fill the VBO with data
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
            
            // Bind the EBO
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            // Fill the EBO with data
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, sizeof(Vertex::Position), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
            
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, sizeof(Vertex::Normal), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, sizeof(Vertex::TexCoords), GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
            
            // unbind VAO to prevent edits to this
            glBindVertexArray(0);

            return Mesh{ vertices, indices, textures, VAO, VBO, EBO };
        }

        static void draw(const Mesh& mesh, const Shader& shader) {
            glBindVertexArray(mesh.VAO);
            Shader::use(shader);

            GLuint diffuseCount, specularCount, i = 0;
            for (const auto& texture : mesh.textures) {
                glActiveTexture(GL_TEXTURE0 + i);
                std::stringstream stream;
                switch (texture.type) {
                case TextureType::Diffuse:
                    stream << TextureReference::typeAsString(texture) << diffuseCount++;
                    break;
                case TextureType::Specular:
                    specularCount++;
                    break;
                }
                i++;
            }
        }
    };
}


#endif