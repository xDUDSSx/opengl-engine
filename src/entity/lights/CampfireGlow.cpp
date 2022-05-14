#include "CampfireGlow.h"
#include "../../Game.h"

void CampfireGlow::update() {
    PointLight::update();
    float offset;
    float time = Game::time;
    time *= 4;
	offset = ((sin(time) + sin(1.3 * time + 5.7)) * 0.5 + 1) * 0.5f; // [0, 1]
    this->color = glm::vec3(1, 0.6 * offset, 0);
    time /= 4;
    time *= 5;
	offset = ((sin(time) + sin(1.3 * time + 5.7)) * 0.5 + 1) * 0.5f; // [0, 1]
    this->intensity = 0.5f + offset * 0.3f;
    time /= 5;
    time *= 2;
	offset = ((sin(time) + sin(1.3 * time + 5.7)) * 0.5 + 1) * 0.5f; // [0, 1]
    this->radius = 6 + 3.0 * offset;
}

std::string CampfireGlow::getName()
{
    if (name.empty())
        return "Campfire glow " + std::to_string(id);
    return name;
}
