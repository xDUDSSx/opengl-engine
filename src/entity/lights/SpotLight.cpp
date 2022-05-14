#include "SpotLight.h"
#include "../../Game.h"
#include "../../Utils.h"

void SpotLight::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
	Light::render(shader, camera, modelMatrix);
    Utils::drawArrow(direction, glm::vec3(1, 0.8, 0), shader, camera, modelMatrix);
}

void SpotLight::create(PhongShader* shader) {
	Light::create(shader);
    lightIcon->textureSets[0]->texture = Game::textures->load("data/textures/spot.png", "diffuse");
}

void SpotLight::setUniforms(const PhongShader& shader, int index) const {
    const std::string prefix = "spotLights[" + std::to_string(index) + "]";
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".intensity").c_str()), intensity);
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".color").c_str()), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".position").c_str()), 1, glm::value_ptr(transform.pos));
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".direction").c_str()), 1, glm::value_ptr(direction));
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".radius").c_str()), radius);
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".cutoffAngle").c_str()), glm::radians(90.0f - cutoffAngle));
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".cutoffSoftAngle").c_str()), glm::radians(90.0f - cutoffSoftAngle));
}

std::string SpotLight::getName() {
    if (name.empty())
        return "Spot Light " + std::to_string(id);
    return name;
}
