#pragma once

#include "pgr.h"
#include "MeshGeometry.h"
#include "../../Camera.h"

class GameObject {

protected:
    glm::vec3 position;
    std::shared_ptr<MeshGeometry> geometry;
    std::shared_ptr<PhongShader> shader;

public:
    GameObject();

    virtual void create(std::shared_ptr<PhongShader> shader);
    virtual void render(std::shared_ptr<Camera> camera) const;
    virtual void update();
};
