#pragma once

#include "Light.h"

class PointLight : public Light {
public:
    float radius = 15.0f;

    void setUniforms(const PhongShader& shader, int index) const override;
};
