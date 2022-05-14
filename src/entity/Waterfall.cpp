#include "Waterfall.h"
#include "../Utils.h"
#include "../Game.h"

void Waterfall::render(PhongShader& shader, Camera& camera, glm::mat4 modelMatrix) {
    glm::mat3 m = glm::mat3(1);
    m *= Utils::translate2D(glm::vec2(0, -Game::time));
    //m *= Utils::rotate2D(fmodf(Game::time * 5, 360));

	textureSets[0]->texture->setUvTransform(m);
    textureSets[0]->normalMap->setUvTransform(m);

	GameObject::render(shader, camera, modelMatrix);
}

void Waterfall::create(PhongShader* shader) {
	GameObject::create(shader);

	loadMesh("data/models/waterfall.obj", true, 25);

	auto tSet = std::make_shared<TextureSet>();
    opaque = false;
    backFaceCull = true;
    tSet->texture = Game::textures->load("data/textures/water.png", "diffuse");
    tSet->normalMap = Game::textures->load("data/textures/Solid_noise_n(15,16,1_2).png", "normal");
    tSet->normalStrength = 0.28f;
	textureSets.push_back(tSet);

    transform.rot = glm::vec3(0, 0, 90);
    transform.scale = glm::vec3(6);
}
