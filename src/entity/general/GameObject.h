#pragma once

#include "Entity.h"
#include "../../Material.h"
#include "pgr.h"
#include "../../Mesh.h"
#include "../../entity/Camera.h"
#include "../../Texture.h"
#include "../../parser/ObjParser.h"

class GameObject : public Entity{
public:
    glm::vec3 rotation;
    glm::vec3 scale;

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    std::shared_ptr<PhongShader> shader;

    std::shared_ptr<Texture> texture;
    std::shared_ptr<Texture> specularMap;
    std::shared_ptr<Texture> aoMap;
    std::shared_ptr<Texture> normalMap;
    std::shared_ptr<Texture> emissionMap;

protected:
    glm::mat4 modelMatrix;

public:
    GameObject();

    virtual void render(PhongShader& shader, Camera& camera);
    virtual void update();
	virtual void create(std::shared_ptr<PhongShader> shader);

    void loadMesh(const char* path, bool arraysOrElements);
};
