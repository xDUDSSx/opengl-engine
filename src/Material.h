#pragma once

#include "pgr.h"
#include "shader/PhongShader.h"

/**
 * \brief Data class holding basic material information.
 */
class Material {
public:
	glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 ambient = diffuse * 0.25f;
	float shininess = 16.0f;

	/**
	 * \brief Set material uniforms for a shader.
	 * \param shader The shader
	 */
	void setUniforms(PhongShader& shader) const;
};
