#pragma once

#include "pgr.h"

#include "Entity.h"
#include "../../Material.h"
#include "../../mesh/Mesh.h"
#include "../../texture/TextureSet.h"
#include "../../Game.h"

/**
 * \brief Basic world object entity. Represents a physical drawable object.
 */
class GameObject : public Entity {
public:
    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<TextureSet>> textureSets;

    GameObject();

    void render(PhongShader& shader, Camera& camera) override;
    void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
    void update() override;
    void create(PhongShader* shader) override;
    void dispose() override;

    std::string getName() override;

    void loadMesh(const char* path, bool arraysOrElements);
    void loadMesh(const char* path, bool arraysOrElements, float uvScale);

    void addEmptyMaterial();
    void addEmptyTextureSet();
};
