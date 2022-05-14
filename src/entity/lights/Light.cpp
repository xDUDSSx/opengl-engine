#include "Light.h"
#include "../../Game.h"

void Light::render(PhongShader& shader, Camera& camera) {
    render(shader, camera, transform.constructMatrix());
}

void Light::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
    lightIcon->render(shader, camera, modelMatrix);
}

void Light::update()
{
    lightIcon->transform.pos = this->transform.pos;
}

void Light::create(PhongShader* shader)
{
    Entity::create(shader);
    this->opaque = false;
    lightIcon = std::make_shared<Billboard>();
    lightIcon->create(shader);
    lightIcon->transform.scale = glm::vec3(0.5f);
    lightIcon->textureSets[0]->texture = Game::textures->load("data/textures/point.png", "diffuse");
}

void Light::updateTransform(glm::mat4 worldMatrix, glm::mat4 parentMatrix) {
	Entity::updateTransform(worldMatrix, parentMatrix);
    lightIcon->worldTransform = this->worldTransform;
}
