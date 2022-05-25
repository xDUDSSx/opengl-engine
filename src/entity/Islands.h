#pragma once

#include "general/GameObject.h"

class Islands : public GameObject {
public:
	void render(PhongShader& shader, Camera& camera) override;
	void update() override;
	void create(PhongShader* shader) override;
};
