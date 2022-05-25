#pragma once

#include "general/GameObject.h"

class Airship : public GameObject {
public:
	void create(PhongShader* shader) override;
};
