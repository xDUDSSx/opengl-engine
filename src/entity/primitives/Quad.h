#pragma once

#include "../general/GameObject.h"

class Quad : public GameObject {
public:
    Quad() = default;

    void render(PhongShader& shader, Camera& camera) override;
    void create(PhongShader* shader) override;
};
