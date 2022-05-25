#pragma once

#include "../general/Entity.h"
#include "../../shader/PhongShader.h"
#include "../primitives/Billboard.h"

class Light : public Entity {
public:
	std::shared_ptr<Billboard> lightIcon;

	glm::vec3 color = glm::vec3(1);
	float intensity = 0.6f;

	void render(PhongShader& shader, Camera& camera) override;
	void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
	void update() override;
	void create(PhongShader* shader) override;
	void dispose() override;

	virtual void setUniforms(const PhongShader& shader, int index) const = 0;

	void updateTransform(glm::mat4 worldMatrix, glm::mat4 parentMatrix) override;
};

inline void Light::dispose() {}
