#pragma once

#include "../general/GameObject.h"

class Quad : public GameObject {
public:
    Quad() = default;

    void create(PhongShader* shader) override;
};
