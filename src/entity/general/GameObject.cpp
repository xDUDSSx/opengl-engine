#include "GameObject.h"

#include "../../parser/ObjParser.h"
#include "../../entity/Camera.h"
#include "../../texture/Texture.h"

GameObject::GameObject() : Entity()
{
    // Empty
}

void GameObject::render(PhongShader& shader, Camera& camera)
{
    render(shader, camera, transform.constructMatrix());
}

void GameObject::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
	// Apply transform
    camera.matrix(shader, modelMatrix);

    for (unsigned int i = 0; i < meshes.size(); i++) {
        if (i >= materials.size()) { //Use default material if not specified
            materials.push_back(std::make_shared<Material>());
        }
        const auto material = materials[i];
        auto tSet = std::shared_ptr<TextureSet>(nullptr);
    	if (i < textureSets.size()) {
            tSet = textureSets[i];
        }

        const auto mesh = meshes[i];

    	// Apply material
        material->setUniforms(shader);

        // Apply texture / maps
        if (tSet != nullptr) {
            if (tSet->texture != nullptr) {
                tSet->texture->bind(0, 0, shader);
            }
            if (tSet->specularMap != nullptr) {
                tSet->specularMap->bind(0, 1, shader);
            }
            if (tSet->normalMap != nullptr) {
                glUniform1f(glGetUniformLocation(shader.id, "normalStrength"), tSet->normalStrength);
                tSet->normalMap->bind(0, 2, shader);
            }
            if (tSet->aoMap != nullptr) {
                tSet->aoMap->bind(0, 3, shader);
            }
            if (tSet->emissionMap != nullptr) {
                tSet->emissionMap->bind(0, 4, shader);
            }
        }

        mesh->render();
    }

    // Clear texture state
    shader.clearTextures();
}

void GameObject::update()
{
	// Empty
}

void GameObject::create(PhongShader* shader)
{
    Entity::create(shader);
}

void GameObject::loadMesh(const char* path, bool arraysOrElements) {
    loadMesh(path, arraysOrElements, 1.0f);
}

void GameObject::loadMesh(const char* path, bool arraysOrElements, float uvScale) {
    ObjParser parser(path, uvScale);
    int triangles = parser.getTriangleCount();
    std::vector<float> vbo;
    Mesh* g = nullptr;
    if (arraysOrElements) {
        parser.getDrawArraysGeo(vbo);
        g = new Mesh(MeshType::TRIANGLES_ARRAYS, vbo.data(), vbo.size(), triangles, *this->shader);
    } else {
        std::vector<unsigned int> ebo;
        parser.getDrawElementsGeo(vbo, ebo);
        g = new Mesh(MeshType::TRIANGLES_ELEMENTS, vbo.data(), vbo.size(), ebo.data(), ebo.size(), triangles, *this->shader);
    }
    this->meshes.push_back(std::shared_ptr<Mesh>(g));
}

void GameObject::addEmptyMaterial() {
    auto material = std::make_shared<Material>();
    materials.push_back(material);
}
void GameObject::addEmptyTextureSet() {
    auto textureSet = std::make_shared<TextureSet>();
    textureSets.push_back(textureSet);
}

void GameObject::dispose() {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        const auto tSet = textureSets[i];
        const auto mesh = meshes[i];

        if (mesh != nullptr) {
            mesh->dispose();
        }
        
        // Apply texture / maps
        if (tSet->texture != nullptr) {
            tSet->texture->dispose();
        }
        if (tSet->specularMap != nullptr) {
            tSet->specularMap->dispose();
        }
        if (tSet->normalMap != nullptr) {
            tSet->normalMap->dispose();
        }
        if (tSet->aoMap != nullptr) {
            tSet->aoMap->dispose();
        }
        if (tSet->emissionMap != nullptr) {
            tSet->emissionMap->dispose();
        }
    }
}

std::string GameObject::getName() {
    if (name.empty())
		return "GameObject" + std::to_string(id);
    return name;
}
