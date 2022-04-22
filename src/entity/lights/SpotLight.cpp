#include "SpotLight.h"

void SpotLight::setUniforms(const PhongShader& shader, int index) const {
    const std::string prefix = "spotLights[" + std::to_string(index) + "]";
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".intensity").c_str()), intensity);
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".color").c_str()), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".position").c_str()), 1, glm::value_ptr(position));
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".direction").c_str()), 1, glm::value_ptr(direction));
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".radius").c_str()), radius);
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".cutoffAngle").c_str()), glm::radians(90.0f - cutoffAngle));
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".cutoffSoftAngle").c_str()), glm::radians(90.0f - cutoffSoftAngle));
}
