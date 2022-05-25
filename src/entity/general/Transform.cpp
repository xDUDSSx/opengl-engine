#include "Transform.h"

glm::mat4 Transform::constructMatrix() const
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, pos);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.x), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.y), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.z), glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, scale);
	return modelMatrix;
}
