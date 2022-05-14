#pragma once
#include "Light.h"

class SunLight : public Light {
public:
    glm::vec3 direction = glm::vec3(0.8, 0, -1);

	void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
	void create(PhongShader* shader) override;

	void setUniforms(const PhongShader& shader, int index) const override;
	std::string getName() override;
};
