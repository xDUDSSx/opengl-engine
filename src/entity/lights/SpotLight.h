#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
	float radius = 70.0f;
	float cutoffAngle = 10;
	float cutoffSoftAngle = 6;
	glm::vec3 direction = glm::vec3(0, 0, -1);

	void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
	void create(PhongShader* shader) override;

	void setUniforms(const PhongShader& shader, int index) const override;
	std::string getName() override;
};
