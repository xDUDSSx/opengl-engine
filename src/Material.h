#pragma once

#include "pgr.h"
#include "shader/PhongShader.h"

class Material {
public:
    glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 ambient = diffuse * 0.25f;
    float shininess = 16.0f;

    void setUniforms(PhongShader& shader) const;
};
