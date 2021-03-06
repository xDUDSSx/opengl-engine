#pragma once

#include "pgr.h"
#include "entity/Camera.h"
#include "texture/Cubemap.h"

/**
 * \brief A skybox implementation that uses and manages a cubemap.
 */
class Skybox {
public:
	GLuint vao;
	GLuint vbo;

	std::shared_ptr<Cubemap> cubemap;

	Skybox(std::shared_ptr<Cubemap> cubemap);

	void render(SkyboxShader& shader, Camera& camera) const;
	void create(SkyboxShader& shader);
	void dispose();
};
