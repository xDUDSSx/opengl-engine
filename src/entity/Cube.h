#pragma once

#include "general/GameObject.h"

class Cube : public GameObject {
public:
    void render(std::shared_ptr<Camera> camera) const override;
    void create(std::shared_ptr<PhongShader> shader) override;
};
