#pragma once

#include "pgr.h"

class Transform {
public:
	glm::vec3 pos = glm::vec3(0.0f);
	glm::vec3 rot = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

	/**
	 * \brief Create a basic transform with default neutral values.
	 */
	Transform() = default;

	/**
	 * \brief Creates a model matrix from the current transform values.
	 */
	glm::mat4 constructMatrix() const;
};
