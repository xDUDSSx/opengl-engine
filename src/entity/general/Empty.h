#pragma once

#include "GameObject.h"

class Empty : public GameObject {
public:
	void create(PhongShader* shader) override;
};
