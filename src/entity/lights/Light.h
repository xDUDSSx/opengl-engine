#pragma once

#include "../general/Entity.h"
#include "../../shader/PhongShader.h"

class Light : public Entity {
public:
    glm::vec3 color = glm::vec3(1);
    float intensity = 0.6f;

    void render(PhongShader& shader, Camera& camera) override;
    void update() override;
    void create(std::shared_ptr<PhongShader> shader) override;

    virtual void setUniforms(const PhongShader& shader, int index) const = 0;
};

inline void Light::render(PhongShader& shader, Camera& camera) {}
inline void Light::update() {}
inline void Light::create(std::shared_ptr<PhongShader> shader) {}
