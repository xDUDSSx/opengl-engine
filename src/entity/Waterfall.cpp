#include "Waterfall.h"
#include "../Utils.h"
#include "../Game.h"

void Waterfall::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
    glm::mat3 m = glm::mat3(1);
    m *= Utils::translate2D(glm::vec2(0, Game::time));
    //m *= Utils::rotate2D(fmodf(Game::time * 5, 360));

	textureSets[0]->texture->setUvTransform(m);
    textureSets[0]->normalMap->setUvTransform(m);

	Quad::render(shader, camera, modelMatrix);
}

void Waterfall::create(PhongShader* shader) {
	Quad::create(shader);
    opaque = false;
	textureSets[0]->texture = std::make_shared<Texture>("data/textures/water.png", "diffuse");
    textureSets[0]->normalMap = std::make_shared<Texture>("data/textures/Solid_noise_n(15,16,1_2).png", "normal");
    textureSets[0]->normalStrength = 0.28f;
}
