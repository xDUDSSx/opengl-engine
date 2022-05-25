#include "Skybox.h"

Skybox::Skybox(std::shared_ptr<Cubemap> cubemap)
{
	this->cubemap = cubemap;
}

void Skybox::render(SkyboxShader& shader, Camera& camera) const
{
	// Apply transform
	camera.matrix(shader);

	// Bind cubemap
	cubemap->bind(shader.samplerId);

	glBindVertexArray(vao);
	CHECK_GL_ERROR();
	glDrawArrays(GL_TRIANGLES, 0, (6 * 2) * 3);

	CHECK_GL_ERROR();
	glBindVertexArray(0);
}

void Skybox::create(SkyboxShader& shader) {
	// Mesh from https://learnopengl.com/code_viewer.php?code=advanced/cubemaps_skybox_data
	float skyboxVertices[] = {
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(skyboxVertices) / sizeof(*skyboxVertices)) * sizeof(float), skyboxVertices, GL_STATIC_DRAW);

	// Just tightly packed positions
	glEnableVertexAttribArray(shader.aPos);
	glVertexAttribPointer(shader.aPos, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	CHECK_GL_ERROR();

	glBindVertexArray(0);
}

void Skybox::dispose() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}
