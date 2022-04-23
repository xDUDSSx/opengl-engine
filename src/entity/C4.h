#pragma once

#include "general/GameObject.h"

class C4 : public GameObject {
public:
    void render(PhongShader& shader, Camera& camera) override;
    void update() override;
    void create(std::shared_ptr<PhongShader> shader) override;
};
