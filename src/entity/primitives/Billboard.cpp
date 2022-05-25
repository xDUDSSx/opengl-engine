#include "Billboard.h"

#include "Arrow.h"
#include "../Camera.h"
#include "../../Utils.h"

Billboard::Billboard() : Quad() {
	this->opaque = false;
}

void Billboard::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
	glm::vec3 toCamera = glm::normalize(camera.worldTransform.pos - worldTransform.pos);
	glm::vec3 upVector = glm::vec3(0, 0, 1);
	glm::vec3 rightVector = glm::normalize(glm::cross(toCamera, upVector));
	glm::vec3 upVectorTransformed = glm::cross(rightVector, toCamera);
	glm::mat4 cameraBasis = glm::mat3(toCamera, rightVector, upVectorTransformed);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, transform.pos);
	modelMatrix = modelMatrix * cameraBasis;
	modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, transform.scale);
	modelMatrix *= parentMatrix;

	glUniform1i(glGetUniformLocation(shader.id, "basic"), true);
	Quad::render(shader, camera, modelMatrix);
	glUniform1i(glGetUniformLocation(shader.id, "basic"), false);
}

