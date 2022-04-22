#pragma once

#include "pgr.h"
#include "../../shader/PhongShader.h"

class Material {
public:
    glm::vec3 diffuse = glm::vec3(0.2, 0.6, 0.3);
    glm::vec3 specular = glm::vec3(0.7, 0.7, 0.7);
    glm::vec3 ambient = diffuse * 0.3f;
    float shininess = 6.0f;

    void setUniforms(PhongShader& shader) const;
};
