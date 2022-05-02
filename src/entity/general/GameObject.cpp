#include "GameObject.h"

#include "../../parser/ObjParser.h"

GameObject::GameObject() : Entity()
{
	// Empty
}

void GameObject::render(PhongShader& shader, Camera& camera)
{
    render(shader, camera, transform.constructMatrix());
}

void GameObject::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
    this->modelMatrix = modelMatrix;

	// Apply transform
    camera.matrix(shader, modelMatrix);

    // Apply material
    material->setUniforms(shader);

    // Apply texture / maps
    if (texture != nullptr) {
        texture->bind(0, 0, shader);
    }
    if (specularMap != nullptr) {
        specularMap->bind(0, 1, shader);
    }
    if (normalMap != nullptr) {
        normalMap->bind(0, 2, shader);
    }
    if (aoMap != nullptr) {
        aoMap->bind(0, 3, shader);
    }
    if (emissionMap != nullptr) {
        emissionMap->bind(0, 4, shader);
    }

    mesh->render();

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
	this->material = std::make_shared<Material>();
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
        g = new Mesh(vbo.data(), vbo.size(), triangles, *this->shader);
    } else {
        std::vector<unsigned int> ebo;
        parser.getDrawElementsGeo(vbo, ebo);
        g = new Mesh(vbo.data(), vbo.size(), ebo.data(), ebo.size(), triangles, *this->shader);
    }
    this->mesh = std::shared_ptr<Mesh>(g);
}

void GameObject::dispose() {
    if (mesh != nullptr) {
        mesh->dispose();
    }

    if (texture != nullptr) {
        texture->dispose();
    }
    if (specularMap != nullptr) {
        specularMap->dispose();
    }
    if (normalMap != nullptr) {
        normalMap->dispose();
    }
    if (aoMap != nullptr) {
        aoMap->dispose();
    }
    if (emissionMap != nullptr) {
        emissionMap->dispose();
    }
}
