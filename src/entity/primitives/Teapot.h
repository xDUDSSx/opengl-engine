#pragma once

#include "../general/GameObject.h"

class Teapot : public GameObject {
public:
    void render(PhongShader& shader, Camera& camera) override;
    void update() override;
    void create(PhongShader* shader) override;
};
