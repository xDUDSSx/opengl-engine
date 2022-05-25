#pragma once

#include "../general/GameObject.h"

class Arrow : public GameObject {
public:
	glm::vec3 vector;
	glm::vec3 color;

	Arrow(glm::vec3 vector, glm::vec3 color);

	void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
	void create(PhongShader* shader) override;
};