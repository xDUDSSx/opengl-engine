#include "Entity.h"

void Entity::create(PhongShader* shader) {
	this->shader = shader;
}

void Entity::updateTransform(glm::mat4 worldMatrix, glm::mat4 parentMatrix)
{
	this->worldMatrix = worldMatrix;
	this->parentMatrix = parentMatrix;
	this->worldTransform.pos = glm::vec3(worldMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

void Entity::setName(std::string name) {
	this->name = name;
}

std::string Entity::getName() {
	if (name.empty()) {
		name = "Entity " + std::to_string(id);
	}
	return name; //TODO: Optimize copying perhaps
}
