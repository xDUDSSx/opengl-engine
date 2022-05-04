#pragma once

#include "../general/Empty.h"

class RotateEmpty : public Empty {
public:
    glm::vec3 axis;
    float speed;

    RotateEmpty(glm::vec3 axis);
    RotateEmpty(glm::vec3 axis, float speed);
	void update() override;
};