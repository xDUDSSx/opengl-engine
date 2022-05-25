#pragma once
#include "Quad.h"

class Billboard : public Quad {
public:
	Billboard();

	void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) override;
};
