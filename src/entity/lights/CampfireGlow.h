#pragma once
#include "PointLight.h"

class CampfireGlow : public PointLight {
public:
	void update() override;
	std::string getName() override;
};
