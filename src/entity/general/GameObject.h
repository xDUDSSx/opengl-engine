#pragma once

#include "Entity.h"
#include "Material.h"
#include "pgr.h"
#include "Mesh.h"
#include "../../entity/Camera.h"

class GameObject : public Entity{
public:
    glm::vec3 rotation;
    glm::vec3 scale;

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    std::shared_ptr<PhongShader> shader;

protected:
    glm::mat4 modelMatrix;

public:
    GameObject();

    virtual void render(std::shared_ptr<Camera> camera);
    virtual void update();
	virtual void create(std::shared_ptr<PhongShader> shader);
};
