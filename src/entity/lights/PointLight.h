#pragma once

#include "Light.h"

class PointLight : public Light {
public:
    float radius = 12.0f;

    void setUniforms(const PhongShader& shader, int index) const override;
    std::string getName() override;
};
