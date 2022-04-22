#pragma once

#include "../general/GameObject.h"

class Quad : public GameObject {
public:
    Quad() = default;

    void render(std::shared_ptr<Camera> camera) override;
    void create(std::shared_ptr<PhongShader> shader) override;
};
