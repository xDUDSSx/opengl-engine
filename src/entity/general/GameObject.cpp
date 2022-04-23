#include "GameObject.h"

GameObject::GameObject() : Entity(),
	rotation(glm::vec3(0)),
	scale(glm::vec3(1))
{
    // Empty
}

void GameObject::render(std::shared_ptr<Camera> camera) {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, scale);

    // Apply transform
    camera->matrix(*this->shader, modelMatrix);

    // Apply material
    material->setUniforms(*shader);

    // Apply texture / maps
    if (texture != nullptr) {
        texture->bind(0, 0, *shader);
    }
    if (specularMap != nullptr) {
        specularMap->bind(0, 1, *shader);
    }
    if (aoMap != nullptr) {
        aoMap->bind(0, 2, *shader);
    }
    if (normalMap != nullptr) {
        normalMap->bind(0, 3, *shader);
    }

    mesh->render();

    // Clear texture state
    shader->clearTextures();
}

void GameObject::update()
{

}

void GameObject::create(std::shared_ptr<PhongShader> shader)
{
    this->shader = shader;
    this->material = std::make_shared<Material>();
}
