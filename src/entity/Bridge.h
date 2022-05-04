#pragma once

#include "general/GameObject.h"

class Bridge : public GameObject {
public:
    void create(PhongShader* shader) override;
};
