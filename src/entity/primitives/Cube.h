#pragma once

#include "../general/GameObject.h"

class Cube : public GameObject {
public:
    void render(std::shared_ptr<Camera> camera) override;
    void update() override;
    void create(std::shared_ptr<PhongShader> shader) override;
};
