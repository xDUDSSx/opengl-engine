#include "Empty.h"

#include "pgr.h"

void Empty::create(PhongShader* shader) {
	GameObject::create(shader);

	wireframe = true;

	addEmptyTextureSet();
	addEmptyMaterial();
	this->materials[0]->diffuse = glm::vec3(0.89, 0.43, 0.09);
	this->materials[0]->specular = glm::vec3(0.5, 0.5, 0.5);

	loadMesh("data/models/empty.obj", false);
}
