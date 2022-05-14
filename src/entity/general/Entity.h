#pragma once

#include "pgr.h"

#include "Transform.h"
#include "../../shader/PhongShader.h"

class Camera;

/**
 * \brief An entity. Holds basic information and a world transform.
 */
class Entity {
public:
	/** Id of the entity, -1 if not assigned, a positive integer otherwise */
	unsigned long id = -1;

	bool opaque = true;
	bool backFaceCull = false;
	bool wireframe = false;
    bool disableLighting = false;
    float alphaCutoff = 0.1f;

	std::string name = "";

	/** \brief Local coordinates transform */
	Transform transform;
	/** \brief World coordinates transform */
	Transform worldTransform;

	/** \brief World transform matrix */
	glm::mat4 worldMatrix = glm::mat4(1);
    /** \brief Entities scene graph parent's world transform matrix */
    glm::mat4 parentMatrix = glm::mat4(1);

	/** \brief Default shader to use when rendering this entity */
    PhongShader* shader = nullptr;

	Entity() = default;
	virtual ~Entity() = default;

	virtual void render(PhongShader& shader, Camera& camera) = 0;
	virtual void render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) = 0;
	virtual void update() = 0;
	virtual void create(PhongShader* shader);
	virtual void dispose() = 0;

	virtual void updateTransform(glm::mat4 worldMatrix, glm::mat4 parentMatrix);

    virtual void setName(std::string name);
	virtual std::string getName();

	friend bool operator==(const Entity& lhs, const Entity& rhs)
	{
		return (lhs.id == rhs.id);
	}

	friend bool operator!=(const Entity& lhs, const Entity& rhs)
	{
		return !(lhs == rhs);
	}
};