#include "C4.h"
#include "../Game.h"

void C4::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void C4::update()
{
	GameObject::update();
}

void C4::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load model
	loadMesh("data/models/c4.obj", true);
	
	// Load texture
	const auto tSet = std::make_shared<TextureSet>();
	tSet->texture = Game::textures->load("data/textures/c4/c4bakeFinal.001_color.jpg", "diffuse");
	tSet->specularMap = Game::textures->load("data/textures/c4/c4bakeFinal.001_specular.jpg", "specular");
	tSet->normalMap = Game::textures->load("data/textures/c4/c4bakeFinal.001_normal.jpg", "normal");
	tSet->aoMap = Game::textures->load("data/textures/c4/c4bakeFinal.001_ao.jpg", "ao");
	tSet->emissionMap = Game::textures->load("data/textures/c4/c4bakeFinal.001_emission.jpg", "emission");

	this->textureSets.push_back(tSet);
}
