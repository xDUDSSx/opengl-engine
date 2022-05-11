#pragma once

#include "primitives/Quad.h"

class Waterfall : public Quad {
public:
    Waterfall() = default;

    void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
    void create(PhongShader* shader) override;
};
