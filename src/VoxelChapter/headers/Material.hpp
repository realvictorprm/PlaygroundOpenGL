#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <glm/glm.hpp>
#include "Shader.hpp"

class Material {
public:
    const glm::vec3 ambient;
    const glm::vec3 diffuse;
    const glm::vec3 specular;
    const float shininess;

    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) 
        : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {

    }

    static void use(const Material& m, Shader& shader) {
        shader.setVec3("material.ambient", m.ambient);
        shader.setVec3("material.diffuse", m.diffuse);
        shader.setVec3("material.specular", m.specular);
        shader.setFloat("material.shininess", m.shininess);
    }
};

Material const GOLD (
    glm::vec3(0.24725, 0.1995, 0.0745),
    glm::vec3(0.75164, 0.60648, 0.22648),
    glm::vec3(0.628281, 0.555802, 0.366065),
    0.4f
);

Material const COPPER {
    glm::vec3(0.19125, 0.0735, 0.0225),
    glm::vec3(0.7038, 0.27048, 0.0828),
    glm::vec3(0.256777, 0.137622, 0.086014),
    0.1f
};

Material const BRONZE {
    glm::vec3(0.2125, 0.1275, 0.054),
    glm::vec3(0.714, 0.4284, 0.18144),
    glm::vec3(0.393548, 0.271906, 0.166721),
    0.2f
};

Material const OBSIDIAN {
    glm::vec3(0.05375, 0.05, 0.06625),
    glm::vec3(0.18275, 0.17, 0.22525),
    glm::vec3(0.332741, 0.328634, 0.346435),
    0.3f
};

Material const SILVER {
    glm::vec3(0.19225, 0.19225, 0.19225),
    glm::vec3(0.50754, 0.50754, 0.50754),
    glm::vec3(0.508273, 0.508273, 0.508273),
    0.3f
};

Material const WHITE{
    glm::vec3(1., 1., 1.),
    glm::vec3(1., 1., 1.),
    glm::vec3(0.1, 0.1, 0.1),
    0.2f
};



#endif