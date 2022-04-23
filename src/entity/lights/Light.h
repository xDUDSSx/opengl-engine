#pragma once

#include "../general/Entity.h"
#include "../../shader/PhongShader.h"

class Light : public Entity {
public:
    glm::vec3 color = glm::vec3(1);
    float intensity = 0.6f;

    virtual void setUniforms(const PhongShader& shader, int index) const = 0;
};