#include "Islands.h"
#include "../Game.h"

void Islands::render(PhongShader& shader, Camera& camera)
{
	GameObject::render(shader, camera);
}

void Islands::update()
{
	GameObject::update();
}

void Islands::create(PhongShader* shader)
{
	GameObject::create(shader);

	// Load model
	loadMesh("data/models/island_new.obj", true, 1);

	// Load textures
	const auto tSet = std::make_shared<TextureSet>();
	tSet->texture = Game::textures->load("data/textures/islands/islands_bake_high_color.jpg", "diffuse");
	tSet->specularMap = Game::textures->load("data/textures/islands/islands_bake_high_specular.jpg", "specular");
	tSet->normalMap = Game::textures->load("data/textures/islands/islands_bake_high_normal.jpg", "normal");
	tSet->aoMap = Game::textures->load("data/textures/islands/islands_bake_high_ao.jpg", "ao");
	this->textureSets.push_back(tSet);
}
