#pragma once

#include "pgr.h"

#include "../../entity/Camera.h"
#include "Transform.h"

class Entity {
public:
    Transform transform;

    Entity() = default;

    virtual void render(PhongShader& shader, Camera& camera) = 0;
    virtual void update() = 0;
    virtual void create(std::shared_ptr<PhongShader> shader) = 0;
};
