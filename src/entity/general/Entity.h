#pragma once

#include "pgr.h"

#include "../../entity/Camera.h"
#include "Transform.h"

class Entity {
public:
	/** Id of the entity, -1 if not assigned, a positive integer otherwise */
	unsigned long id = -1;

	bool opaque = true;
    bool backFaceCull = false;

	Transform transform;
	glm::mat4 worldMatrix = glm::mat4(1);

	PhongShader* shader;

	Entity() = default;
	virtual ~Entity() = default;

	virtual void render(PhongShader& shader, Camera& camera) = 0;
	virtual void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) = 0;
	virtual void update() = 0;
	virtual void create(PhongShader* shader);
	virtual void dispose() = 0;

	friend bool operator==(const Entity& lhs, const Entity& rhs)
	{
		return (lhs.id == rhs.id);
	}

	friend bool operator!=(const Entity& lhs, const Entity& rhs)
	{
		return !(lhs == rhs);
	}
};