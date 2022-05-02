#pragma once

#include "pgr.h"

#include "Entity.h"
#include "../../Material.h"
#include "../../Mesh.h"
#include "../../entity/Camera.h"
#include "../../texture/Texture.h"

class GameObject : public Entity {
public:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;

    std::shared_ptr<Texture> texture;
    std::shared_ptr<Texture> specularMap;
    std::shared_ptr<Texture> normalMap;
	std::shared_ptr<Texture> aoMap;
    std::shared_ptr<Texture> emissionMap;

protected:
    //TODO: Think this is unused?
    glm::mat4 modelMatrix;

public:
    GameObject();

    void render(PhongShader& shader, Camera& camera) override;
    void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
    void update() override;
    void create(PhongShader* shader) override;
    void dispose() override;

    void loadMesh(const char* path, bool arraysOrElements);
    void loadMesh(const char* path, bool arraysOrElements, float uvScale);
};
