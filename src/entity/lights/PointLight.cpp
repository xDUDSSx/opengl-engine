#include "PointLight.h"
#include "../../Game.h"

void PointLight::create(PhongShader* shader) {
	Light::create(shader);
	lightIcon->textureSets[0]->texture = Game::textures->load("data/textures/point.png", "diffuse");
}

void PointLight::setUniforms(const PhongShader& shader, int index) const {
	const std::string prefix = "pointLights[" + std::to_string(index) + "]";
	glUniform1f(glGetUniformLocation(shader.id, (prefix + ".intensity").c_str()), intensity);
	glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".color").c_str()), 1, glm::value_ptr(color));
	glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".position").c_str()), 1, glm::value_ptr(transform.pos));
	glUniform1f(glGetUniformLocation(shader.id, (prefix + ".radius").c_str()), radius);
}

std::string PointLight::getName()
{
	if (name.empty())
		return "Point Light " + std::to_string(id);
	return name;
}
