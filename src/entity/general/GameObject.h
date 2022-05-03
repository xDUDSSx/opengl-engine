#pragma once

#include "pgr.h"

#include "Entity.h"
#include "../../Material.h"
#include "../../Mesh.h"
#include "../../entity/Camera.h"
#include "../../texture/Texture.h"
#include "../../texture/TextureSet.h"

class GameObject : public Entity {
public:
    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<TextureSet>> textureSets;

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

    void addEmptyMaterial();
    void addEmptyTextureSet();
};
