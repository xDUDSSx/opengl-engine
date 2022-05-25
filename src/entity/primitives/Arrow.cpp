#include "Arrow.h"

#include "../../entity/Camera.h"

Arrow::Arrow(glm::vec3 vector, glm::vec3 color)
	: GameObject()
	, vector(vector)
	, color(color)
{
	// Empty
}

void Arrow::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
	camera.matrix(shader, modelMatrix);
	glUniform1i(glGetUniformLocation(shader.id, "basic"), true);
	const auto mesh = meshes[0];
	glBindVertexArray(mesh->vao);
	glDrawArrays(GL_LINES, 0, 2);
	CHECK_GL_ERROR();
	glBindVertexArray(0);
	glUniform1i(glGetUniformLocation(shader.id, "basic"), false);
}

void Arrow::create(PhongShader* shader) {
	GameObject::create(shader);

	addEmptyMaterial();
	addEmptyTextureSet();

	//Create mesh
	//unsigned int vertsCount = 2 * 11;
	//float verts[] = {
	//    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	//    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	//};
	unsigned int vertsCount = 2 * 6;
	float verts[] = {
		0.0f, 0.0f, 0.0f, color.x, color.y, color.z, 
		vector.x, vector.y, vector.z, color.x, color.y, color.z
	};
	unsigned int lines = 2;

	Mesh* mesh = new Mesh();

	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertsCount * sizeof(float), verts, GL_STATIC_DRAW);

	const size_t vertexSize = 6 * sizeof(float);

	glEnableVertexAttribArray(shader->aPos);
	glVertexAttribPointer(shader->aPos, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0);

	glEnableVertexAttribArray(shader->aColor);
	glVertexAttribPointer(shader->aColor, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(3 * sizeof(float)));

	/*glEnableVertexAttribArray(shader->aTexCoord);
	glVertexAttribPointer(shader->aTexCoord, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(shader->aNormal);
	glVertexAttribPointer(shader->aNormal, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(5 * sizeof(float)));

	glEnableVertexAttribArray(shader->aTangent);
	glVertexAttribPointer(shader->aTangent, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(8 * sizeof(float)));*/

	CHECK_GL_ERROR();

	glBindVertexArray(0);

	this->meshes.push_back(std::shared_ptr<Mesh>(mesh));
}
