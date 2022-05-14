#include "SunLight.h"
#include "../../Game.h"
#include "../../Utils.h"

void SunLight::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
	Light::render(shader, camera, modelMatrix);
    Utils::drawArrow(direction, glm::vec3(1, 0.8, 0), shader, camera, modelMatrix);
}

void SunLight::create(PhongShader* shader) {
	Light::create(shader);
    lightIcon->textureSets[0]->texture = Game::textures->load("data/textures/sun.png", "diffuse");
}

void SunLight::setUniforms(const PhongShader& shader, int index) const {
    const std::string prefix = "sunLights[" + std::to_string(index) + "]";
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".intensity").c_str()), intensity);
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".color").c_str()), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".direction").c_str()), 1, glm::value_ptr(direction));
}

std::string SunLight::getName() {
    if (name.empty())
        return "Sun Light " + std::to_string(id);
    return name;
}
